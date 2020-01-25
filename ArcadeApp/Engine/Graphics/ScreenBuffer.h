#pragma once
#include "Colour.h"

struct SDL_Surface;

class ScreenBuffer 
{
public:
	ScreenBuffer() :m_surface(nullptr) {}
	ScreenBuffer(const ScreenBuffer& otherBuffer);
	~ScreenBuffer();

	ScreenBuffer& operator=(const ScreenBuffer& otherBuffer);

	void Init(uint32_t format, uint32_t width, uint32_t height);

	void Clear(const Colour& colour = Colour::Black());

	void SetPixel(const Colour& colour, int x, int y);

	inline SDL_Surface * GetSurface() { return m_surface; }

private:
	uint32_t GetIndex(int row, int col);

	SDL_Surface* m_surface;
};

