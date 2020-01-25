#include <iostream>
#include <assert.h>
#include <algorithm>

#include "Screen.h"

#include "../Maths/Vector2.h"

#include "../Shapes/Triangle.h"
#include "../Shapes/AARect.h"
#include "../Shapes/Circle.h"

#include "../Utils/Utils.h"

Screen::~Screen()
{
	if (m_pWindow)
	{
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}
		SDL_Quit();
}
SDL_Window* Screen::Init(uint32_t width, uint32_t height, uint32_t magnification)
{

	//Initialises SDL Library (specifically the video display)
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Error SDL_Init Failed" << std::endl;
		return nullptr;
	}

	m_width = width;
	m_height = height;

	m_pWindow = SDL_CreateWindow("Arcade App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width * magnification, m_height * magnification, 0);

	if (m_pWindow)
	{
		//1D array of pixels
		m_pSurface = SDL_GetWindowSurface(m_pWindow);

		SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
		Colour::InitPixelColourFormat(pixelFormat);

		m_clearColour = Colour::Black();
		m_backBuffer.Init(pixelFormat->format, m_width, m_height);
		m_backBuffer.Clear(m_clearColour);
	}

	return m_pWindow;
}

void Screen::SwapBuffers()
{
	assert(m_pWindow);

	if (m_pWindow)
	{
		ClearBuffers();
		SDL_BlitScaled(m_backBuffer.GetSurface(), nullptr, m_pSurface, nullptr);
		SDL_UpdateWindowSurface(m_pWindow);
		m_backBuffer.Clear(m_clearColour);
	}
}

void Screen::Draw(int x, int y, const Colour& colour)
{
	assert(m_pWindow);

	if (m_pWindow)
		m_backBuffer.SetPixel(colour, x, y);
}

void Screen::Draw(const Vector2& point, const Colour& colour)
{
	assert(m_pWindow);

	if (m_pWindow)
		m_backBuffer.SetPixel(colour, point.GetX(), point.GetY());
}

void Screen::Draw(const Line& line, const Colour& colour)
{
	assert(m_pWindow);

	if (m_pWindow)
	{
		int dx, dy;

		int x = roundf(line.GetPoint().GetX());
		int y = roundf(line.GetPoint().GetY());
		int x1 = roundf(line.GetPoint1().GetX());
		int y1 = roundf(line.GetPoint1().GetY());

		dx = x1 - x;
		dy = y1 - y;

		signed const char ix((dx > 0) - (dx < 0)); // evaluate to 1 or -1
		signed const char iy((dy > 0) - (dy < 0));

		dx = abs(dx) * 2;
		dy = abs(dy) * 2;

		Draw(x, y, colour);

		if (dx >= dy)
		{
			//go along in the x

			int d = dy - dx / 2;

			while (x != x1)
			{
				if (d >= 0)
				{
					d -= dx;
					y += iy;
				}

				d += dy;
				x += ix;

				Draw(x, y, colour);
			}
		}
		else
		{
			//go along in y
			int d = dx - dy / 2;

			while (y != y1)
			{
				if (d >= 0)
				{
					d -= dy;
					x += ix;
				}

				d += dx;
				y += iy;

				Draw(x, y, colour);
			}
		}
	}
}

void Screen::Draw(const Triangle& triangle, const Colour& colour, bool fillPoly, const Colour& fillColour)
{
	if (fillPoly)
		FillPoly(triangle.GetPoints(), fillColour);

	Line line = Line(triangle.GetPoint(), triangle.GetPoint1());
	Line line1 = Line(triangle.GetPoint1(), triangle.GetPoint2());
	Line line2 = Line(triangle.GetPoint2(), triangle.GetPoint());

	Draw(line, colour);
	Draw(line1, colour);
	Draw(line2, colour);
}

void Screen::Draw(const AARect& rect, const Colour& colour, bool fillPoly, const Colour& fillColour)
{
	if (fillPoly)
		FillPoly(rect.GetPoints(), fillColour);

	std::vector<Vector2> points = rect.GetPoints();

	Line line = Line(points[0], points[1]);
	Line line1 = Line(points[1], points[2]);
	Line line2 = Line(points[2], points[3]);
	Line line3 = Line(points[3], points[0]);

	Draw(line, colour);
	Draw(line1, colour);
	Draw(line2, colour);
	Draw(line3, colour);
}

void Screen::Draw(const Circle& circle, const Colour& colour, bool fillPoly, const Colour& fillColour)
{
	static unsigned int NUM_CIRCLE_SEGS = 30;

	std::vector<Vector2> circlePoints;
	std::vector<Line> lines;

	float angle = TWO_PI / float(NUM_CIRCLE_SEGS);
	
	Vector2 point = Vector2(circle.GetCentrePoint().GetX() + circle.GetRadius(), circle.GetCentrePoint().GetY());
	Vector2 point1 = point;

	Line nextLine;

	for (unsigned int i = 0; i < NUM_CIRCLE_SEGS; ++i)
	{
		point1.Rotate(angle, circle.GetCentrePoint());

		nextLine.SetPoint1(point1);
		nextLine.SetPoint(point);

		lines.push_back(nextLine);

		point = point1;
		circlePoints.push_back(point);
	}

	if (fillPoly)
		FillPoly(circlePoints, fillColour);

	for (const Line& line : lines)
		Draw(line, colour);
}

void Screen::ClearBuffers()
{
	assert(m_pWindow);

	if (m_pWindow)
		SDL_FillRect(m_pSurface, nullptr, m_clearColour.GetPixelColour());
}

void Screen::FillPoly(const std::vector<Vector2>& points, const Colour& colour)
{
	//Scan line polygon filling algorithm

	if (points.size() > 0)
	{
		//Set defaults
		float top = points[0].GetY();
		float bottom = points[0].GetY();
		float right = points[0].GetX();
		float left = points[0].GetX();

		//search through points and find most extreme
		for (size_t i = 1; i < points.size(); ++i)
		{
			if (points[i].GetY() < top)
			{
				top = points[i].GetY();
			}
			if (points[i].GetY() > bottom)
			{  
				bottom = points[i].GetY();
			}
			if (points[i].GetX() < left)
			{
				left = points[i].GetX();
			}
			if (points[i].GetX() > right)
			{
				right = points[i].GetX();
			}
		}

		//Iterate through pixels
		for (int i = top; i < bottom; ++i)
		{
			std::vector<float> xintercept;

			size_t last = points.size() - 1;

			//iterate through points
			for (size_t j = 0; j < points.size(); ++j)
			{
				float currentY = points[j].GetY();
				float lastY = points[last].GetY();

				//if pixelY is between point and last point.
				if ((currentY <= static_cast<float>(i) && lastY > static_cast<float>(i) || lastY <= static_cast<float>(i) && currentY > static_cast<float>(i)))
				{
					float demoninator = lastY - currentY;
					if(bIsEqualTo(demoninator, 0))
						continue;
					
					//find x intercept
					float x = points[j].GetX() + (i - currentY) / (demoninator) * (points[last].GetX() - points[j].GetX());
					xintercept.push_back(x);
				}

				last = j;
			}

			std::sort(xintercept.begin(), xintercept.end(), std::less<>());

			//bounding x
			for (size_t k = 0; k < xintercept.size(); k += 2)
			{
				if (xintercept[k] > right)
					break;

				if (xintercept[k + 1] > left)
				{
					if (xintercept[k] < left)
						xintercept[k] = left;

					if (xintercept[k + 1] > right)
						xintercept[k + 1] = right;

					for (int j = xintercept[k]; j < xintercept[k + 1]; ++j)
					{
						Draw(j, i, colour);
					}
				}
			}
		}
	}
}
