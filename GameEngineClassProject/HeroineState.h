#ifndef HEROINE_STATE_H
#define HEROINE_STATE_H

#include "StandardIncludes.h"

class Heroine;
class IdleState;
class RollState;
class PaperState;
class ScissorsState;
class RockState;

class HeroineState
{
public:
	HeroineState() {}
	virtual ~HeroineState() {}

	static IdleState* GetIdleState() { return &m_idle; }
	static RollState* GetRollState() { return &m_roll; }
	static PaperState* GetPaperState() { return &m_paper; }
	static ScissorsState* GetScissorsState() { return &m_scissors; }
	static RockState* GetRockState() { return &m_rock; }

	virtual void HandleInput(Heroine* _heroine, SDL_Event _event) = 0;
	virtual void Update(Heroine* _heroine, float _deltaTime) = 0;

private:
	static IdleState m_idle;
	static RollState m_roll;
	static PaperState m_paper;
	static ScissorsState m_scissors;
	static RockState m_rock;
};

class IdleState : public HeroineState
{
public:
	IdleState() {}
	virtual ~IdleState() {}

	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};

class RollState : public HeroineState
{
public:
	RollState() {}
	virtual ~RollState() {}

	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;;
};

class PaperState : public HeroineState
{
public:
	PaperState() {}
	virtual ~PaperState() {}
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;;
};

class ScissorsState : public HeroineState
{
public:
	ScissorsState() {}
	virtual ~ScissorsState() {}
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;;
};

class RockState : public HeroineState
{
public:
	RockState() {}
	virtual ~RockState() {}
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;;
};

#endif