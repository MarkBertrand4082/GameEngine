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
#include "RenderTarget.h"
#include "Timing.h"



GameController::GameController()
{
	m_sdlEvent = {};
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_quit = false;
	m_input = nullptr;
	m_audio = nullptr;
	m_player = nullptr;
	m_timer = nullptr;
	m_upHeld = false;
	m_downHeld = false;
	m_leftHeld = false;
	m_rightHeld = false;
	m_npcs = {};
	memset(m_effects, 0, sizeof(SoundEffect*) * MaxEffectChannels);


}

GameController::~GameController()
{
	ShutDown();
}

void GameController::Initialize()
{
	AssetController::Instance().Initialize(10000000);
	
	m_audio = &AudioController::Instance();
	m_effects[0] = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	m_player = new Unit();
	m_timer = &Timing::Instance();
	m_player->AssignNonDefaultValues();
	
	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_input = &InputController::Instance();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_timer->SetFPS(80);

	m_rt = new RenderTarget();
	m_rt->Create(m_renderer->GetWindowSize().X, m_renderer->GetWindowSize().Y);

	glm::vec2 middle = { m_renderer->GetWindowSize().X / 2, m_renderer->GetWindowSize().Y / 2 };

	m_player->SetX1(middle[0]);
	m_player->SetY1(middle[1]);
	m_player->SetLoc(middle);
	m_player->SetX2(middle[0] + 69 * 1.25);
	m_player->SetY2(middle[1] + 44 * 1.25);

	for (int i = 0; i < 10; i++)
	{
		m_npcs.push_back(new Unit());
		m_npcs[i]->SetLoc({});
	}
}

void GameController::ShutDown()
{
	delete m_fArial20;
	delete m_player;
	delete m_rt;
}

void GameController::HandleInput(SDL_Event _event)
{
	if ((_event.type == SDL_QUIT) || (m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	
	else if(m_input->KB()->KeyDown(_event, SDLK_UP))
	{
		if (!m_upHeld)
		{
			m_player->SetDir(m_player->GetDir() + up);
			m_upHeld = true;
		}
		m_player->SetMoving(true);
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN))
	{
		if (!m_downHeld)
		{
			m_player->SetDir(m_player->GetDir() + down);
			m_downHeld = true;
		}
		m_player->SetMoving(true);
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT))
	{
		if (!m_leftHeld)
		{
			m_player->SetDir(m_player->GetDir() + left);
			m_leftHeld = true;
		}
		m_player->SetMoving(true);
		m_player->SetFlip(true);
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT))
	{
		if (!m_rightHeld)
		{
			m_player->SetDir(m_player->GetDir() + right);
			m_rightHeld = true;
		}
		m_player->SetMoving(true);
		m_player->SetFlip(false);
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_UP))
	{
		if (m_upHeld)
		{
			m_player->SetMoving(false);
			m_upHeld = false;
			m_player->SetDir(m_player->GetDir() - up);
		}
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_DOWN))
	{
		if(m_downHeld)
		{
			m_player->SetMoving(false);
			m_downHeld = false;
			m_player->SetDir(m_player->GetDir() - down);
		}
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_LEFT))
	{
		if (m_leftHeld)
		{
			m_player->SetMoving(false);
			m_leftHeld = false;
			m_player->SetDir(m_player->GetDir() - left);
		}
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_RIGHT))
	{
		if (m_rightHeld)
		{
			m_player->SetMoving(false);
			m_rightHeld = false;
			m_player->SetDir(m_player->GetDir() - right);
		}
	}
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

		m_fArial20->Write(m_renderer->GetRenderer(), glm::to_string(m_player->GetDir()).c_str(), SDL_Color{ 0,255,0 }, SDL_Point{250,200});
		
		m_player->SetX1(m_player->GetX1() + m_player->GetDir()[0]);
		m_player->SetX2(m_player->GetX2() + m_player->GetDir()[0]);
		m_player->SetY1(m_player->GetY1() + m_player->GetDir()[1]);
		m_player->SetY2(m_player->GetY2() + m_player->GetDir()[1]);

		

		for (int i = 0; i < 10; i++) //This handles animations for the NPCs
		{
			
			if (glm::distance(m_npcs[i]->GetLoc(), m_npcs[i]->GetLoc()) < 150)
			{
				cout << glm::distance(m_npcs[i]->GetLoc(), m_npcs[i]->GetLoc());
			}

			if (!m_npcs[i]->GetCaught())
			{
				if (m_npcs[i]->GetMoving())
				{
					m_renderer->RenderTexture(m_npcs[i]->GetSheet(), m_npcs[i]->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_npcs[i]->GetX2(), m_npcs[i]->GetY1(), m_npcs[i]->GetX1(), m_npcs[i]->GetY2()));
				}
				else
				{
					m_renderer->RenderTexture(m_player->GetSheet(), m_npcs[i]->GetSheet()->Update(EN_AN_IDLE, m_timer->GetDeltaTime()), Rect(m_npcs[i]->GetX2(), m_npcs[i]->GetY1(), m_npcs[i]->GetX1(), m_npcs[i]->GetY2()));
				}
			}
		}
		//m_rt->Start();
		//m_rt->Stop();
		//m_renderer->SetDrawColor(Color(0, 0, 0, 50));
		//m_renderer->ClearScreen();

		if (m_player->GetMoving())
		{
			if (m_player->GetFlip())	
			{
				m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_player->GetX2(), m_player->GetY1(), m_player->GetX1(), m_player->GetY2()));
			}
			else
			{
				m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_player->GetX1(), m_player->GetY1(), m_player->GetX2(), m_player->GetY2()));
			}
			
		}
		else if(SDL_PollEvent(&m_sdlEvent) == 0)
		{
			m_player->SetMoving(false);
			if (m_player->GetFlip()) {
				m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_IDLE, m_timer->GetDeltaTime()), Rect(m_player->GetX2(), m_player->GetY1(), m_player->GetX1(), m_player->GetY2()));
			}
			else 
			{
				m_renderer->RenderTexture(m_player->GetSheet(), m_player->GetSheet()->Update(EN_AN_IDLE, m_timer->GetDeltaTime()), Rect(m_player->GetX1(), m_player->GetY1(), m_player->GetX2(), m_player->GetY2()));
			}
		}

		
		

		m_rt->Render(m_timer->GetDeltaTime());
		
		SDL_RenderPresent(m_renderer->GetRenderer());

		m_timer->CapFPS();
	}

}	