#include "Physics.h"
#include "Unit.h"

Physics::Physics()
{
	m_falling = new Subject();
}

Physics::~Physics()
{
	delete m_falling;
}

void Physics::Update(Unit* _unit)
{
	if (_unit->GetLastY() > _unit->GetY())
	{
		m_falling->Notify(_unit, "UnitFalling");
	}
}