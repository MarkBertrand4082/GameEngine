#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "StandardIncludes.h"

struct ControllerInfo
{
	SDL_JoystickID ID = -1;
	SDL_GameController* Controller = nullptr;
	string Name;
};

class Controller
{
public:
	Controller();
	virtual ~Controller();

	vector<ControllerInfo>& GetControllers() { return m_controllers; }

	void DetectControllers();
	bool Added(SDL_Event _event);
	bool Removed(SDL_Event _event);

	string ToString();

private:
	void Add(SDL_GameController* _controller, int _controllerID);

	vector<ControllerInfo> m_controllers;
};

#endif