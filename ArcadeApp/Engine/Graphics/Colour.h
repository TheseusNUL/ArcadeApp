#pragma once
#include <stdint.h>
#include <SDL.h>

struct SDL_PixelFormat;

class Colour
{
public:
	Colour() : Colour(0) {}
	Colour(uint32_t colour) : m_colour(colour) {}
	Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	static void InitPixelColourFormat(const SDL_PixelFormat* format);

	/*------------------------------------------------------------------------------------------------------------------------
		The following functions are dependant on the pixel format so InitPixelColourFormat() must be called before
		their use. By making them static they can be called without the need for an instance to be created first
		as there is only one version of the function shared between all instances. By making them functions however, and not
		members, memory is potentially saved as the colours are only created once the function is called.
	-------------------------------------------------------------------------------------------------------------------------*/
	static Colour BlendAlpha(const Colour& source, const Colour& destination);

	static Colour Black() { return Colour(0, 0, 0, 255); }
	static Colour White() { return Colour(255, 255, 255, 255); }
	static Colour Blue() { return Colour(0, 0, 255, 255); }
	static Colour Red() { return Colour(255, 0, 0, 255); }
	static Colour Green() { return Colour(0, 255, 0, 255); }
	static Colour Yellow() { return Colour(255, 255, 0, 255); }
	static Colour Magenta() { return Colour(255, 0, 255, 255); }
	static Colour Cyan() { return Colour(37, 240, 217, 255); }
	static Colour Pink() { return Colour(252, 197, 224, 255); }
	static Colour Orange() { return Colour(245, 190, 100, 255); }
	/*----------------------------------------------------------------------------------------------------------------------------*/

	inline bool operator==(const Colour& other) const {return m_colour == other.m_colour;}
	inline bool operator!=(const Colour& other) const { return !(*this == other); }
	inline uint32_t GetPixelColour() const { return m_colour; }

	void SetPixelRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	void SetPixelRed(uint8_t red);
	void SetPixelGreen(uint8_t green);
	void SetPixelBlue(uint8_t blue);
	void SetPixelAlpha(uint8_t alpha);

	uint8_t GetPixelRed() const;
	uint8_t GetPixelGreen() const;
	uint8_t GetPixelBlue() const;
	uint8_t GetPixelAlpha() const;

	static const SDL_PixelFormat* m_format;

private:
	uint32_t m_colour;
};