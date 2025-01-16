#pragma once
#include <string>

class NoCommandDemo
{
public:
	void HandleInput(std::string _button);

private:
	void Jump();
	void FireGun();
	void SwapWeapon();
	void Lurch();
};

