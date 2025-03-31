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
class WavDraw;
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
	WavDraw* m_wavDraw;
	SoundEffect* m_effects[MaxEffectChannels];
	Timing* m_timer;
	int m_zoomY;
	int m_playerX1;
	int m_playerY1;
	int m_playerX2;
	int m_playerY2;
};

#endif