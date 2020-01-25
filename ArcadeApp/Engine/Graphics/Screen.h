#pragma once
#include <vector>

#include "ScreenBuffer.h"

#include "../Shapes/Line.h"

class Vector2;
class Triangle;
class AARect;
class Circle;
struct SDL_Window;
struct SDL_Surface;

class Screen
{
public:
	Screen() : m_width(0), m_height(0), m_pWindow(nullptr), m_pSurface(nullptr) {}
	~Screen();

	//The screen should not be copied
	Screen(const Screen& screen) = delete;
	Screen& operator=(const Screen& screen) = delete;

	inline void SetClearColour(const Colour& clearColour) { m_clearColour = clearColour; }
	inline uint32_t GetWidth() const { return m_width; }
	inline uint32_t GetHeight() const { return m_height; }

	SDL_Window* Init(uint32_t width, uint32_t height, uint32_t magnification);
	void SwapBuffers();

	void Draw(int x, int y, const Colour& colour);
	void Draw(const Vector2& point, const Colour& colour);
	void Draw(const Line& line, const Colour& colour);
	void Draw(const Triangle& triangle, const Colour& colour, bool fillPoly = false, const Colour& fillColour = Colour::White());
	void Draw(const AARect& rect, const Colour& colour, bool fillPoly = false, const Colour& fillColour = Colour::White());
	void Draw(const Circle& circle, const Colour& colour, bool fillPoly = false, const Colour& fillColour = Colour::White());

private:
	void ClearBuffers();
	void FillPoly(const std::vector<Vector2>& points, const Colour& colour);

	uint32_t m_width;
	uint32_t m_height;

	Colour m_clearColour;
	ScreenBuffer m_backBuffer;

	SDL_Window* m_pWindow;
	SDL_Surface* m_pSurface;
};
