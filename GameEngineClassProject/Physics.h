#pragma once
#include "Subject.h"
#include "Singleton.h"

class Unit;

class Physics :public Singleton<Physics>
{
public:
	Physics();
	virtual ~Physics();

	Subject* GetEventFalling() { return m_falling; }

	void Update(Unit* _unit);

private:
	Subject* m_falling;
};

