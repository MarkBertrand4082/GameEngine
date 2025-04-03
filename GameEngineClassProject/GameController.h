#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "AudioController.h"
#include "Unit.h"

class Renderer;
class TTFont;
class InputController;
class AudioController;
class SoundEffect;
class Song;
class RenderTarget;
class Timing;

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
	Unit* m_player;
	vector<Unit*> m_enemies;
	SDL_Event m_sdlEvent;
	Renderer* m_renderer;
	TTFont* m_fArial20;
	bool m_quit;
	InputController* m_input;
	AudioController* m_audio;
	RenderTarget* m_rt;
	SoundEffect* m_effects[MaxEffectChannels];
	vector<Unit*> m_npcs;
	Timing* m_timer;
	glm::vec2 left = { -1,0 };
	glm::vec2 right = { 1,0 };
	glm::vec2 up = { 0,-1};
	glm::vec2 down = {0,1 };
	bool m_upHeld;
	bool m_downHeld;
	bool m_leftHeld;
	bool m_rightHeld;

};

#endif