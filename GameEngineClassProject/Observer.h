#pragma once
#include <string>

class Unit;

class Observer
{
public:
	virtual ~Observer(){}
	virtual void OnNotify(Unit* _unit, std::string _event) = 0;
};

