#pragma once
#include <string>
#include <vector>

#include "Command.h"

class Unit;

class CommandDemo
{
public:
	CommandDemo();
	virtual ~CommandDemo();
	void HandleInput(std::string _button);
	void Undo();

private:
	std::vector<Command*> m_commands;
	Unit* m_unit;
};

