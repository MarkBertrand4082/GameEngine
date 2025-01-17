#include "Command.h"
#include "Unit.h"


class CommandMoveUnit : public Command
{
public: 
	CommandMoveUnit(Unit* _unit, int _x, int _y)
	{
		m_unit = _unit;
		m_xBefore = 0;
		m_yBefore = 0;
		m_x = _x;
		m_y = _y;
	}

	virtual void Execute()
	{
		m_xBefore = m_unit->GetX();
		m_yBefore = m_unit->GetY();	
		m_unit->MoveTo(m_x, m_y);
	}

	virtual void Undo()
	{
		m_unit->MoveTo(m_xBefore, m_yBefore);
	}

private:
	Unit* m_unit;
	int m_xBefore;
	int m_yBefore;
	int m_x;
	int m_y;
};

