#include <iostream>

#include "NoCommandDemo.h"

void NoCommandDemo::Jump() {
	
	std::cout << "Jump!\n";
}

void NoCommandDemo::FireGun() {
	
	std::cout << "Fire Gun!\n";
}

void NoCommandDemo::SwapWeapon() {

	std::cout << "Swap Weapon!\n";
}

void NoCommandDemo::Lurch() {

	std::cout << "Lurch!\n";
}

void NoCommandDemo::HandleInput(std::string _button) {
	
	if (_button == "X") Jump();
	else if (_button == "Y") FireGun();
	else if (_button == "A") SwapWeapon();
	else if (_button == "B") Lurch();
}