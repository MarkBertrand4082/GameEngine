#ifndef LEVEL2_H
#define LEVEL2_H

#include "Unit.h"

class Renderer;
class AudioController;
class PhysicsController;
class InputController;
class Timing;
class TTFont;

class Level2 : public Resource
{
public:
	Level2(Renderer* _r, AudioController* _a, PhysicsController* _p, InputController* _i, Timing* _t, TTFont* _font, string _n1, string _n2);
	virtual ~Level2();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void Play();
	void HandleInput(SDL_Event _event);

private:
	SDL_Event m_sdlEvent;
	bool m_quit;
	Renderer* m_r;
	AudioController* m_a;
	PhysicsController* m_p;
	InputController* m_input;
	Timing* m_timing;
	TTFont* m_fArial20;
	string m_name1;
	string m_name2;

	//otehr interesting level members
};
#endif
