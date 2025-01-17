#include "Subject.h"
#include "Observer.h"
#include "Unit.h"

void Subject::Notify(Unit* _unit, std::string _event)
{
	for (int i = 0; i < m_observers.size(); i++)
	{
		m_observers[i]->OnNotify(_unit, _event);
	}
}

void Subject::AddObserver(Observer* _observer)
{
	m_observers.push_back(_observer);
}

void Subject::RemoveObserver(Observer* _observer)
{
	auto pos = std::find(m_observers.begin(), m_observers.end(), _observer);
	m_observers.erase(pos);
}