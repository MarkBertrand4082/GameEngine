#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include "StandardIncludes.h"

class RenderTarget
{
public:
	RenderTarget();
	virtual ~RenderTarget();

	void Create(unsigned int _width, unsigned int _height);
	void Start();
	void Stop();
	void Render(float _deltaTime);

private:
	SDL_Texture* m_texture;
	unsigned int m_width;
	unsigned int m_height;
	float m_rotation;
};

#endif