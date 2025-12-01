#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"

class Renderer;
class TTFont;
class InputController;
class Timing;
class PhysicsController;
class SpriteSheet;
class AudioController;
class Heroine;

class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController();

	void RunGame();
	void Initialize();
	void HandleInput(SDL_Event _event);
	void ShutDown();		

private:
	SDL_Event m_sdlEvent;
	Renderer* m_renderer;
	TTFont* m_fArial20;
	bool m_quit;
	InputController* m_input;
	Timing* m_timing;
	PhysicsController* m_physics;
	Heroine* m_heroine;
	AudioController* m_audio;

};

#endif