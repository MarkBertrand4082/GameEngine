#include "GameController.h"
#include "Renderer.h"
#include "TTFont.h"	
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "AudioController.h"
#include "SoundEffect.h"
#include "Song.h"
#include "WavDraw.h"
#include "Timing.h"


GameController::GameController()
{
	m_sdlEvent = {};
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_quit = false;
	m_input = nullptr;
	m_audio = nullptr;
	m_wavDraw = nullptr;
	m_player = nullptr;
	m_timer = nullptr;
	memset(m_effects, 0, sizeof(SoundEffect*) * MaxEffectChannels);
	m_zoomY = 5;
	m_playerX1 = 0.0;
	m_playerY1 = 0.0;
	m_playerX2 = 0.0;
	m_playerY2 = 0.0;

}

GameController::~GameController()
{
	ShutDown();
}

void GameController::Initialize()
{
	AssetController::Instance().Initialize(10000000);
	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_input = &InputController::Instance();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_audio = &AudioController::Instance();
	m_effects[0] = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	m_player = new Unit();
	m_timer = &Timing::Instance();
	

}

void GameController::ShutDown()
{
	delete m_fArial20;
}

void GameController::HandleInput(SDL_Event _event)
{
	if ((_event.type == SDL_QUIT) || (m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_UP))
	{
		m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_playerX1, m_playerY1, m_playerX2, m_playerY2));
		m_playerY1 -= 10;
		m_playerY2 -= 10;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN))
	{
		m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_playerX1, m_playerY1, m_playerX2, m_playerY2));
		m_playerY1 += 10;
		m_playerY2 += 10;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT))
	{
		m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_playerX1, m_playerY1, m_playerX2, m_playerY2));
		m_playerX1 -= 10;
		m_playerX2 -= 10;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT))
	{
		m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_playerX1, m_playerY1, m_playerX2, m_playerY2));
		m_playerX1 += 10;
		m_playerX2 += 10;
	}
	else
	{
		m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_IDLE, m_timer->GetDeltaTime()), Rect(m_playerX1, m_playerY1, m_playerX2, m_playerY2));
	}
	m_input->MS()->ProcessButtons(_event);
}

void GameController::RunGame()
{
	Initialize();
	m_input->CT()->DetectControllers();
	
		
	while (!m_quit)
	{
		m_timer->Tick();
		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}
		
		SDL_RenderPresent(m_renderer->GetRenderer());

		m_timer->CapFPS();
	}

}	