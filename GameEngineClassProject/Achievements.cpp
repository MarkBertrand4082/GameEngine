#include <iostream>

#include "Unit.h"
#include "Achievements.h"

void Achievements::OnNotify(Unit* _unit, std::string _event)
{
	if ((_event == "UnitFalling") && (_unit->GetY() < 0))
	{
		UnlockAchievement("Died From Falling");
	}
}

void Achievements::UnlockAchievement(std::string _achievement)
{
	std::cout << "Achievement Unlocked:" << _achievement << "!!\n";
}