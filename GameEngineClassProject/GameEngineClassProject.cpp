#include <iostream>

#include "Unit.h"
#include "Physics.h"
#include "Achievements.h"

int main()
{
    Achievements* achievements = new Achievements();
    Physics* physics = new Physics();
    Unit* unit = new Unit();

    physics->GetEventFalling()->AddObserver(achievements);
    unit->MoveTo(0, 1);
    physics->Update(unit);
    unit->MoveTo(0, 0);
    physics->Update(unit);
    unit->MoveTo(0, -1);
    physics->Update(unit);

    delete unit;
    delete physics;
    delete achievements;
}
