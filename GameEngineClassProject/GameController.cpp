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

	glm::vec2 middle = { m_renderer->GetWindowSize().X / 2 +1, m_renderer->GetWindowSize().Y / 2 +1 };

	m_player->SetX1(middle[0]);
	m_player->SetY1(middle[1]);
	m_player->SetLoc(middle);
	m_player->SetX2(middle[0] + 69 * 1.25);
	m_player->SetY2(middle[1] + 44 * 1.25);
	m_player->SetSpeed(1.25);

	for (int i = 0; i < 10; i++)
	{
		int ran1 = rand() % 300 - 150;
		int ran2 = rand() % 300 - 150;
		glm::vec2 random = { (m_renderer->GetWindowSize().X / 2) + ran1, (m_renderer->GetWindowSize().Y / 2) + ran2 };

		m_npcs.push_back(new Unit());
		m_npcs[i]->SetLoc(random);
		m_npcs[i]->SetX1(random[0]);
		m_npcs[i]->SetY1(random[1]);
		m_npcs[i]->SetX2(random[0] + 69 * 1.25);
		m_npcs[i]->SetY2(random[1] + 44 * 1.25);
		m_npcs[i]->SetSpeed(.75);
		m_npcs[i]->AssignNonDefaultValues();
	}
}

void GameController::ShutDown()
{
	for (int i =0; i < 10; i++)
	{
		delete m_npcs[i];
	}
	delete m_fArial20;
	delete SpriteSheet::Pool;
	delete SpriteAnim::Pool;
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
	else if (m_input->KB()->KeyDown(_event, SDLK_s))
	{
		ofstream writeStream("assignment3.bin", ios::out | ios::binary);
		m_player->Serialize(writeStream);
		for (int i = 0; i < 10; i++)
		{
			m_npcs[i]->Serialize(writeStream);
		}
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_l))
	{
		ifstream readStream("assignment3.bin", ios::in | ios::binary);
		m_player->Deserialize(readStream);
		for (int i = 0; i < 10; i++)
		{
			m_npcs[i]->Deserialize(readStream);
		}
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_i))
	{
		if (m_npcs[0]->GetSpeed() != .75)
		{
			for (int i = 0; i < 10; i++)
			{
				m_npcs[i]->SetSpeed(m_npcs[i]->GetSpeed() + 0.125);
			}
			
		}
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_d))
	{
		if (m_npcs[0]->GetSpeed() != 0)
		{
			for (int i = 0; i < 10; i++)
			{
				m_npcs[i]->SetSpeed(m_npcs[i]->GetSpeed() - 0.125);
			}

		}
		}
}

void GameController::RunGame()
{
	Initialize();
	m_input->CT()->DetectControllers();
	int deaths = 0;
		
	while (!m_quit)
	{
		m_timer->Tick();
		
		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();
		

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		m_fArial20->Write(m_renderer->GetRenderer(), "[D]ecrease Speed   [I]ncrease Speed   [S]ave   [L]oad   [ESC] Quit", SDL_Color{0,0,255}, SDL_Point{0,0});
		string s1 = "Player Speed: " + to_string(m_player->GetSpeed() * 80);
		m_fArial20->Write(m_renderer->GetRenderer(), s1.c_str(), SDL_Color{0,0,255}, SDL_Point{0,50});
		string s2 = "Enemy Speed: " + to_string(m_npcs[0]->GetSpeed() * 80);
		m_fArial20->Write(m_renderer->GetRenderer(), s2.c_str(), SDL_Color{0,0,255}, SDL_Point{0,100});
		
		m_player->SetX1(m_player->GetX1() + m_player->GetDir()[0] * m_player->GetSpeed());
		m_player->SetX2(m_player->GetX2() + m_player->GetDir()[0] * m_player->GetSpeed());
		m_player->SetY1(m_player->GetY1() + m_player->GetDir()[1] * m_player->GetSpeed());
		m_player->SetY2(m_player->GetY2() + m_player->GetDir()[1] * m_player->GetSpeed());
		m_player->SetLoc(glm::vec2{ m_player->GetX1(), m_player->GetY1() });


		//Player animation logic
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
		else if (SDL_PollEvent(&m_sdlEvent) == 0)
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

		deaths = 0;//This is to count the # of dead npcs at the end of the loop	

		//This handles animations for the NPCs
		for (int i = 0; i <m_npcs.size(); i++) 
		{

			if (!m_npcs[i]->GetDead())
			{
				if (glm::distance(m_npcs[i]->GetLoc(), m_player->GetLoc()) <= 30)
				{
					m_npcs[i]->SetCaught(true);
				}

				//angle of warrior facing player
				int angle = int(atan((m_npcs[i]->GetLoc()[1] - m_player->GetLoc()[1]) / (m_npcs[i]->GetLoc()[0] - m_player->GetLoc()[0])) * 180 / 3.1415);
				if (angle<0 && angle>-90)
				{
					angle -= 90;
				}
				else if (angle < -90)
				{
					angle -= 90;
				}
				else if (angle >= 0)
				{
					angle -= 90;
				}

				if (m_npcs[i]->GetX1() >= m_player->GetX1())
				{
					angle += 180;

				}

				if (!m_npcs[i]->GetCaught())
				{
					if (glm::distance(m_npcs[i]->GetLoc(), m_player->GetLoc()) < 140)
					{

						glm::vec2 move = m_npcs[i]->GetLoc() - m_player->GetLoc();

						if (move[0] < 0)
						{
							m_npcs[i]->SetX1(m_npcs[i]->GetX1() - m_npcs[i]->GetSpeed());
							m_npcs[i]->SetX2(m_npcs[i]->GetX2() - m_npcs[i]->GetSpeed());
						}
						else
						{
							m_npcs[i]->SetX1(m_npcs[i]->GetX1() + m_npcs[i]->GetSpeed());
							m_npcs[i]->SetX2(m_npcs[i]->GetX2() + m_npcs[i]->GetSpeed());
						}
						if (move[1] < 0)
						{
							m_npcs[i]->SetY1(m_npcs[i]->GetY1() - m_npcs[i]->GetSpeed());

							m_npcs[i]->SetY2(m_npcs[i]->GetY2() - m_npcs[i]->GetSpeed());
						}
						else
						{
							m_npcs[i]->SetY1(m_npcs[i]->GetY1() + m_npcs[i]->GetSpeed());

							m_npcs[i]->SetY2(m_npcs[i]->GetY2() + m_npcs[i]->GetSpeed());
						}

						m_npcs[i]->SetLoc(glm::vec2{ m_npcs[i]->GetX1(), m_npcs[i]->GetY1() });
						m_renderer->RenderTexture(m_npcs[i]->GetSheet(), m_npcs[i]->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_npcs[i]->GetX1(), m_npcs[i]->GetY1(), m_npcs[i]->GetX2(), m_npcs[i]->GetY2())
							, angle);
					}
					else if (glm::distance(m_npcs[i]->GetLoc(), m_player->GetLoc()) > 160)
					{
						glm::vec2 move = m_npcs[i]->GetLoc() - m_player->GetLoc();

						if (move[0] < 0)
						{
							m_npcs[i]->SetX1(m_npcs[i]->GetX1() + m_npcs[i]->GetSpeed());
							m_npcs[i]->SetX2(m_npcs[i]->GetX2() + m_npcs[i]->GetSpeed());
						}
						else
						{
							m_npcs[i]->SetX1(m_npcs[i]->GetX1() - m_npcs[i]->GetSpeed());
							m_npcs[i]->SetX2(m_npcs[i]->GetX2() - m_npcs[i]->GetSpeed());
						}
						if (move[1] < 0)
						{
							m_npcs[i]->SetY1(m_npcs[i]->GetY1() + m_npcs[i]->GetSpeed());

							m_npcs[i]->SetY2(m_npcs[i]->GetY2() + m_npcs[i]->GetSpeed());
						}
						else
						{
							m_npcs[i]->SetY1(m_npcs[i]->GetY1() - m_npcs[i]->GetSpeed());

							m_npcs[i]->SetY2(m_npcs[i]->GetY2() - m_npcs[i]->GetSpeed());
						}

						m_npcs[i]->SetLoc(glm::vec2{ m_npcs[i]->GetX1(), m_npcs[i]->GetY1() });
						m_renderer->RenderTexture(m_npcs[i]->GetSheet(), m_npcs[i]->GetSheet()->Update(EN_AN_RUN, m_timer->GetDeltaTime()), Rect(m_npcs[i]->GetX1(), m_npcs[i]->GetY1(), m_npcs[i]->GetX2(), m_npcs[i]->GetY2())
							, angle);
					}
					else
					{

						m_renderer->RenderTexture(m_npcs[i]->GetSheet(), m_npcs[i]->GetSheet()->Update(EN_AN_IDLE, m_timer->GetDeltaTime()), Rect(m_npcs[i]->GetX1(), m_npcs[i]->GetY1(), m_npcs[i]->GetX2(), m_npcs[i]->GetY2())
							, angle);



					}
				}
				else
				{//Death
					m_renderer->RenderTexture(m_npcs[i]->GetSheet(), m_npcs[i]->GetSheet()->Update(EN_AN_DEATH, m_timer->GetDeltaTime()), Rect(m_npcs[i]->GetX1(), m_npcs[i]->GetY1(), m_npcs[i]->GetX2(), m_npcs[i]->GetY2())
						, angle);

					if (m_npcs[i]->GetSheet()->GetCurrentClip(EN_AN_DEATH) == 36)
					{
						m_audio->Play(m_effects[0]);
						m_npcs[i]->SetDead(true);
					}
				}
			
			}
			else
			{
				deaths += 1;
				
				if (deaths == 10)
				{
					exit(0);
				}
			}
			
		}
		string stuff = "Enemies Tagged: " + deaths;
		m_fArial20->Write(m_renderer->GetRenderer(), stuff.c_str(), SDL_Color{0,255,0}, SDL_Point{0,150});
		//m_rt->Start();
		//m_rt->Stop();
		//m_renderer->SetDrawColor(Color(0, 0, 250, 50));
		//m_renderer->ClearScreen();

		
		SDL_RenderPresent(m_renderer->GetRenderer());

		m_timer->CapFPS();
	}

}	