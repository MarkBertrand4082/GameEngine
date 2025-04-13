#include "GameController.h"
#include "Renderer.h"
#include "TTFont.h"	
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "PhysicsController.h"
#include "Timing.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "Particle.h"
#include "RigidBody.h"
#include "Heroine.h"
#include "Level.h"
#include "Level2.h"
#include "AudioController.h"



GameController::GameController()
{
	m_sdlEvent = {};
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_quit = false;
	m_input = nullptr;
	m_timing = nullptr;
	m_physics = nullptr;
	m_heroine = nullptr;
	m_audio = nullptr;
}

GameController::~GameController()
{
	ShutDown();
}

void GameController::Initialize()
{
	AssetController::Instance().Initialize(10000000);
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_input = &InputController:: Instance();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_timing = &Timing::Instance();
	m_physics = &PhysicsController::Instance();
	m_audio = &AudioController::Instance();
}

void GameController::ShutDown()
{
	if (m_heroine != nullptr)
	{
		delete m_heroine;
		m_heroine = nullptr;
	}

	if (m_fArial20 != nullptr)
	{
		delete m_fArial20;
		m_fArial20 = nullptr;
	}
	if (SpriteAnim::Pool != nullptr)
	{
		delete SpriteAnim::Pool;
		SpriteAnim::Pool = nullptr;
	}
	if (SpriteSheet::Pool != nullptr)
	{
		delete SpriteSheet::Pool;
		SpriteSheet::Pool = nullptr;
	}
}

void GameController::HandleInput(SDL_Event _event)
{
	if ((_event.type == SDL_QUIT) || (m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}

	m_input->MS()->ProcessButtons(_event);
}

void GameController::RunGame()
{
	Initialize();
	m_timing->SetFPS(60);
	Level* level = new Level(m_renderer, m_audio, m_physics, m_input, m_timing, m_fArial20 );
	level->Play();
	
	if (!level->GetQuit())
	{
		Level2* level2 = new Level2(m_renderer, m_audio, m_physics, m_input, m_timing, m_fArial20, level->GetText1(), level->GetText2());
		level2->Play();
		delete level2;
	}

	delete level;
	

	ShutDown();

}	