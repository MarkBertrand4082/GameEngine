#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"

class Renderer;
class AudioController;
class PhysicsController;
class InputController;
class Timing;
class TTFont;
class Song;

class Level : public Resource
{
public:
	Level(Renderer* _r, AudioController* _a, PhysicsController* _p, InputController* _i, Timing* _t, TTFont* _font);
	virtual ~Level();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void Play();
	void HandleInput(SDL_Event _event);

	bool GetQuit() { return m_quit; }
	string GetText1() { return m_text; }
	string GetText2() { return m_text2; }

private:
	SDL_Event m_sdlEvent;
	float m_gameTime;
	bool m_quit;
	Renderer* m_r;
	AudioController* m_a;
	PhysicsController* m_p;
	InputController* m_input;
	Timing* m_timing;
	TTFont* m_fArial20;
	TTFont* m_fArial40;
	string m_text;
	string m_text2;
	bool m_text1Done;
	bool m_text2Done;
	Song* m_song;
	string m_error;
	float m_timer;

	//otehr interesting level members
};
#endif
