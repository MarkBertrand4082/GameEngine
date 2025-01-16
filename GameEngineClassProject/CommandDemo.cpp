#include <iostream>

#include "CommandDemo.h"
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
	m_commandJump = new CommandJump();
	m_commandFireGun = new CommandFire();
	m_commandSwapWeapon = new CommandSwap();
	m_commandLurch = new CommandLurch();
}

CommandDemo::~CommandDemo() {
	delete m_commandJump;
	delete m_commandFireGun;
	delete m_commandSwapWeapon;
	delete m_commandLurch;
}

void CommandDemo::HandleInput(std::string _button) {

	if (_button == "X") m_commandJump->Execute();
	else if (_button == "Y") m_commandFireGun->Execute();
	else if (_button == "A") m_commandSwapWeapon->Execute();
	else if (_button == "B") m_commandLurch->Execute();
}