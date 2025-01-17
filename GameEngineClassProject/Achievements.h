#pragma once
#include "Observer.h"

class Achievements : public Observer
{
public:
	virtual void OnNotify(Unit* _unit, std::string _event);

private:
	void UnlockAchievement(std::string _achievement);
};

