#include <cstring>

#include "Colour.h"

const SDL_PixelFormat* Colour::m_format = nullptr;

Colour::Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	SetPixelRGBA(red, green, blue, alpha);


	//m_colour = 0;
	//
	//red = 40;
	//green = 100;
	//blue = 180;
	//alpha = 255;

	//std::memcpy(reinterpret_cast<char*>(&m_colour) + 0,	&red, 1);
	//std::memcpy(reinterpret_cast<char*>(&m_colour) + 1, &green, 1);
	//std::memcpy(reinterpret_cast<char*>(&m_colour) + 2, &blue, 1);
	//std::memcpy(reinterpret_cast<char*>(&m_colour) + 3, &alpha, 1);
}

void Colour::InitPixelColourFormat(const SDL_PixelFormat* format)
{
	//Class namespace is optional here but good practice to access static members this way.
	Colour::m_format = format;
}

Colour Colour::BlendAlpha(const Colour& source, const Colour& destination)
{
	//SourceRBG * SourceAlpha + DestinationRBG * (1 - SourceAlpha) <--- returns value between 0 and 1

	uint8_t alpha = source.GetPixelAlpha();
	
	float sourceAlpha = static_cast<float>(alpha) / 255.0f;
	float destAlpha = 1.0f - sourceAlpha;

	Colour output;

	uint8_t r = static_cast<float>(source.GetPixelRed()) * sourceAlpha + static_cast<float>(destination.GetPixelRed()) * destAlpha;
	uint8_t g = static_cast<float>(source.GetPixelGreen()) * sourceAlpha + static_cast<float>(destination.GetPixelGreen()) * destAlpha;
	uint8_t b = static_cast<float>(source.GetPixelBlue()) * sourceAlpha + static_cast<float>(destination.GetPixelBlue()) * destAlpha;
	uint8_t a = static_cast<float>(source.GetPixelAlpha()) * sourceAlpha + static_cast<float>(destination.GetPixelAlpha()) * destAlpha;

	output.SetPixelAlpha(a);
	output.SetPixelRed(r);
	output.SetPixelGreen(g);
	output.SetPixelBlue(b);

	return output;
}

void Colour::SetPixelRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	m_colour = SDL_MapRGBA(m_format, red, green, blue, alpha);
}

void Colour::SetPixelRed(uint8_t red)
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	SetPixelRGBA(red, lgreen, lblue, lalpha);
}

void Colour::SetPixelGreen(uint8_t green)
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	SetPixelRGBA(lred, green, lblue, lalpha);
}

void Colour::SetPixelBlue(uint8_t blue)
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	SetPixelRGBA(lred, lgreen, blue, lalpha);

}

void Colour::SetPixelAlpha(uint8_t alpha)
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	SetPixelRGBA(lred, lgreen, lblue, alpha);
}

uint8_t Colour::GetPixelRed() const
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	return lred;
}

uint8_t Colour::GetPixelGreen() const
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	return lgreen;
}

uint8_t Colour::GetPixelBlue() const
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	return lblue;
}

uint8_t Colour::GetPixelAlpha() const
{
	uint8_t lred;
	uint8_t lgreen;
	uint8_t lblue;
	uint8_t lalpha;

	SDL_GetRGBA(m_colour, m_format, &lred, &lgreen, &lblue, &lalpha);
	return lalpha;
}
