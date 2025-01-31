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
	
}