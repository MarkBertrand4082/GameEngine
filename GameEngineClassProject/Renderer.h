#ifndef RENDERER_H
#define RENDERER_H

#include "StandardIncludes.h"

struct Color
{
	Color(byte _r, byte _g, byte _b, byte _a)
	{
		R = _r;
		G = _g;
		B = _b;
		A = _a;
	}

	byte R;
	byte G;
	byte B;
	byte A;
};

class Renderer : public Singleton<Renderer>
{
public:
	Renderer();
	virtual ~Renderer();

	SDL_Window* GetWindow() { return m_window;  }
	SDL_Renderer* GetRenderer() { return m_renderer; }

private:
	SDL_Window* m_window;
	SDL_Renderer

#endif