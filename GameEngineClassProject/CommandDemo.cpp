#include <iostream>

#include "CommandDemo.h"
#include "CommandMoveUnit.h"
#include "Command.h"

class CommandJump : public Command {

public:
	CommandJump() {}
	virtual void Execute() { std::cout << "Jump!\n"; }
};

class CommandFire : public Command {

public:
	virtual void Execute() { std::cout << "Fire Gun!\n"; }
};

class CommandSwap : public Command {

public:
	virtual void Execute() { std::cout << "Swap Weapon!\n"; }
};

class CommandLurch : public Command {

public:
	virtual void Execute() { std::cout << "Lurch!\n"; }
};


CommandDemo::CommandDemo()
{
	m_unit = new Unit();
}

CommandDemo::~CommandDemo() {
	delete m_unit;
}

void CommandDemo::HandleInput(std::string _button) {

	//CommandMoveUnit* moveCommand = nullptr;
	//if (_button == "W") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX(), m_unit->GetY() + 1);
	//else if (_button == "A") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX() - 1, m_unit->GetY());
	//else if (_button == "S") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX(), m_unit->GetY() - 1);
	//else if (_button == "D") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX() + 1, m_unit->GetY());

	//if (moveCommand != nullptr)
	//{
	//	moveCommand->Execute();
	//	m_commands.push_back(moveCommand);
	//}
}

void CommandDemo::Undo()
{
	Command* lastCommand = m_commands.back();
	lastCommand->Undo();
	delete lastCommand;
	m_commands.pop_back();
}