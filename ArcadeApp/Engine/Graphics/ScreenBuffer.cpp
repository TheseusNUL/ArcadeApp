#include <cassert>

#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(const ScreenBuffer& otherBuffer)
{
	*this = otherBuffer;
}

ScreenBuffer::~ScreenBuffer()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& otherBuffer)
{
	if (this == &otherBuffer)
		return *this;

	//if surface has data already in it, delete that data
	if (m_surface != nullptr)
	{
		SDL_FreeSurface(m_surface);
		m_surface = nullptr;
	}

	//if other surface has data in it, assign that data to the new instance
	if (otherBuffer.m_surface != nullptr)
	{
		m_surface = SDL_CreateRGBSurfaceWithFormat(0, otherBuffer.m_surface->w, otherBuffer.m_surface->h, 0, otherBuffer.m_surface->format->format);

		SDL_BlitSurface(otherBuffer.m_surface, nullptr, m_surface, nullptr);
	}

	return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height)
{
	m_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
	Clear();
}


void ScreenBuffer::Clear(const Colour& colour)
{
	//aborts program if there is no surface
	assert(m_surface);

	if (m_surface)
		SDL_FillRect(m_surface, nullptr, colour.GetPixelColour());
}

void ScreenBuffer::SetPixel(const Colour& colour, int x, int y)
{
	assert(m_surface);

	if (m_surface)
	{
		//checks if the parameters are within the confides of the pixel array.
		if ((x < m_surface->w && x >= 0) && (y < m_surface->h && y >= 0))
		{
			SDL_LockSurface(m_surface);

			uint32_t* pixels = (uint32_t*)m_surface->pixels;
			size_t index = GetIndex(y, x);
			Colour surfaceColour = Colour(pixels[index]); //colour currently in the buffer

			if (surfaceColour.GetPixelColour() > 0)
			{
				int a = 2;
			}

			//pixels[index] = colour.GetPixelColour();
			pixels[index] = Colour::BlendAlpha(colour, surfaceColour).GetPixelColour(); //Blend with the input colour.

			SDL_UnlockSurface(m_surface);
		}
	}
}

uint32_t ScreenBuffer::GetIndex(int row, int col)
{
	assert(m_surface);

	if (m_surface)
		return row * m_surface->w + col;

	return 0;
}
