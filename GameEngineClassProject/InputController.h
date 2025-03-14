#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "StandardIncludes.h"

class Keyboard;
class Mouse;

class InputController : public Singleton<InputController>
{
public:
	InputController();
	virtual ~InputController();

	Keyboard* KB() { return m_keyboard; }
	Mouse* MS() { return m_mouse; }

private:
	Keyboard* m_keyboard;
	Mouse* m_mouse;
};

#endif