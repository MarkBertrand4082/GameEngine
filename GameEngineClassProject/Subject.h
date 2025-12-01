#pragma once
#include <vector>
#include <string>

class Observer;
class Unit;

class Subject
{
public:
	void AddObserver(Observer* _observer);
	void RemoveObserver(Observer* _observer);
	void Notify(Unit* _unit, std::string _event);

private:
	std::vector<Observer*> m_observers;
};

