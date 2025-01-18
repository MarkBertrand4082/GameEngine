#include <iostream>

#include "Unit.h"
#include "Physics.h"
#include "Achievements.h"

int main()
{
    Achievements* achievements = new Achievements();
    Unit* unit = new Unit();

    Physics::Instance().GetEventFalling()->AddObserver(achievements);
    unit->MoveTo(0, 1);
    unit->MoveTo(0, 0);
    unit->MoveTo(0, -1);
    Physics::Instance().Update(unit);

    delete unit;
    delete achievements;
}
