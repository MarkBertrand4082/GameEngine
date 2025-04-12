#ifndef HEROINE_STATE_H
#define HEROINE_STATE_H

#include "StandardIncludes.h"

class Heroine;
class StandingState;
class DuckingState;
class JumpingState;
class DivingState;

class HeroineState
{
public:
	HeroineState() {}
	virtual ~HeroineState() {}

	static StandingState* GetStandingState() { return &m_standing; }
	static DuckingState* GetDuckingState() { return &m_ducking; }
	static JumpingState* GetJumpingState() { return &m_jumping; }
	static DivingState* GetDivingState() { return &m_diving; }

	virtual void HandleInput(Heroine* _heroine, SDL_Event _event) = 0;
	virtual void Update(Heroine* _heroine, float _deltaTime) = 0;

private:
	static StandingState m_standing;
	static DuckingState m_ducking;
	static JumpingState m_jumping;
	static DivingState m_diving;
};

class StandingState : public HeroineState
{
public:
	StandingState() {}
	virtual ~StandingState() {}

	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};

class DuckingState : public HeroineState
{
public:
	DuckingState() {}
	virtual ~DuckingState() {}

	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;;
};

class JumpingState : public HeroineState
{
public:
	JumpingState() {}
	virtual ~JumpingState() {}
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;;
};

class DivingState : public HeroineState
{
public:
	DivingState() {}
	virtual ~DivingState() {}
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;;
};

#endif