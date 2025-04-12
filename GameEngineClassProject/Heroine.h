#ifndef HEROINE_H
#define HEROINE_H

#include "HeroineState.h"
#include "RigidBody.h"

class SpriteSheet;

class Heroine
{
public:
	Heroine();
	virtual ~Heroine();

	HeroineState* GetState() { return m_state; }
	void SetState(HeroineState* _state) { m_state = _state; }
	SpriteSheet* GetAnimations() { return m_animations; }
	RigidBody* GetRigidBody() { return m_rigidBody; }
	Rect* GetSrcRect() { return &m_srcRect; }

	virtual void HandleInput(SDL_Event _event, float _deltaTime);
	virtual void Update(float _deltaTime);
	virtual void Render(Renderer* _renderer);

private:
	HeroineState* m_state;
	RigidBody* m_rigidBody;
	SpriteSheet* m_animations;
	Rect m_srcRect;
};

#endif