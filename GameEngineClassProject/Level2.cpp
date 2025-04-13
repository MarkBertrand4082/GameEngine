#include "Level2.h"

#include "Renderer.h"
#include "TTFont.h"	
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "PhysicsController.h"
#include "AudioController.h"
#include "Timing.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "Particle.h"
#include "RigidBody.h"
#include "Heroine.h"
#include "SoundEffect.h"

Level2::Level2(Renderer* _r, AudioController* _a, PhysicsController* _p, InputController* _i, Timing* _t, TTFont* _font, string _n1, string _n2)
{
	AssetController::Instance().Initialize(10000000);
	SoundEffect::Pool = new ObjectPool<SoundEffect>();
	m_sdlEvent = {};
	m_r = _r;
	m_a = _a;
	m_p = _p;
	m_input = _i;
	m_timing = _t;
	m_fArial20 = _font;
	m_name1 = _n1;
	m_name2 = _n2;
	m_fist1 = nullptr;
	m_fist2 = nullptr;
	m_quit = false;
	m_wins1 = 0;
	m_wins2 = 0;
}

Level2::~Level2()
{
	AssetController::Instance().Clear();
}

void Level2::AssignNonDefaultValues()
{

	Resource::AssignNonDefaultValues();
}

void Level2::Serialize(std::ostream& _stream)
{

	Resource::Serialize(_stream);
}

void Level2::Deserialize(std::istream& _stream)
{

	Resource::Deserialize(_stream);
}

void Level2::ToString()
{
	cout << "Level2" << endl;
	Resource::ToString();
}

void Level2::Play()
{
	m_fist1 = new Heroine();
	m_fist2 = new Heroine();
	while (!m_quit)
	{
		m_timing->Tick();

		m_r->SetDrawColor(Color{ 255,255,255,255 });
		m_r->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		m_p->Update(m_timing->GetDeltaTime());
		m_fist1->Update(m_timing->GetDeltaTime());
		m_fist2->Update(m_timing->GetDeltaTime());
		m_fist1->Render(m_r);
		m_fist2->Render(m_r);

		Win();

		m_fArial20->Write(m_r->GetRenderer(), m_name1.c_str(), SDL_Color{ 0,255,0 }, SDL_Point{ 50,65 });
		m_fArial20->Write(m_r->GetRenderer(), m_state1.c_str(), SDL_Color{ 255,0,0 }, SDL_Point{ 50,75 });
		//m_fArial20->Write(m_r->GetRenderer(), m_name1.c_str(), SDL_Color{ 0,255,0 }, SDL_Point{ 50,65 });

		m_fArial20->Write(m_r->GetRenderer(), m_name2.c_str(), SDL_Color{ 0,255,0 }, SDL_Point{ 50,210 });
		m_fArial20->Write(m_r->GetRenderer(), m_state2.c_str(), SDL_Color{ 255,0,0 }, SDL_Point{ 50,220 });
		//m_fArial20->Write(m_r->GetRenderer(), m_name2.c_str(), SDL_Color{ 0,255,0 }, SDL_Point{ 50,210 });

		SDL_RenderPresent(m_r->GetRenderer());

		//m_timing->CapFPS();
	}
}

void Level2::HandleInput(SDL_Event _event)
{
	string temp;
	if ((_event.type == SDL_QUIT) || (m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	m_fist1->HandleInput(_event, m_timing->GetDeltaTime());
	m_fist2->HandleInput(_event, m_timing->GetDeltaTime());
	m_input->MS()->ProcessButtons(_event);
}

void Level2::Win()
{
	if (m_fist1->GetState() == HeroineState::GetIdleState() && m_fist2->GetState() == HeroineState::GetIdleState())
	{
		m_state1 = "Waiting to start...";
		m_state2 = "Waiting to start...";
	}
	else if (m_fist1->GetState() == HeroineState::GetRollState() && m_fist2->GetState() == HeroineState::GetRollState())
	{
		m_state1 = "Rolling...";
		m_state2 = "Rolling...";
	}
	else if (m_fist1->GetState() == HeroineState::GetPaperState())
	{
		if (m_fist2->GetState() == HeroineState::GetScissorsState())
		{
			m_state1 = "LOSER!";
			m_state2 = "WINNER!";
		}
		else if (m_fist2->GetState() == HeroineState::GetRockState())
		{
			m_state1 = "WINNER!";
			m_state2 = "LOSER!";
		}
		else if (m_fist2->GetState() == HeroineState::GetPaperState())
		{
			m_state1 = "DRAW!";
			m_state2 = "DRAW!";
		}
	}
	else if (m_fist1->GetState() == HeroineState::GetScissorsState())
	{
		if (m_fist2->GetState() == HeroineState::GetRockState())
		{
			m_state1 = "LOSER!";
			m_state2 = "WINNER!";
		}
		else if (m_fist2->GetState() == HeroineState::GetPaperState())
		{
			m_state1 = "WINNER!";
			m_state2 = "LOSER!";
		}
		else if (m_fist2->GetState() == HeroineState::GetScissorsState())
		{
			m_state1 = "DRAW!";
			m_state2 = "DRAW!";
		}
	}
	else if (m_fist1->GetState() == HeroineState::GetRockState())
	{
		if (m_fist2->GetState() == HeroineState::GetPaperState())
		{
			m_state1 = "LOSER!";
			m_state2 = "WINNER!";
		}
		else if (m_fist2->GetState() == HeroineState::GetScissorsState())
		{
			m_state1 = "WINNER!";
			m_state2 = "LOSER!";
		}
		else if (m_fist2->GetState() == HeroineState::GetRockState())
		{
			m_state1 = "DRAW!";
			m_state2 = "DRAW!";
		}
	}
}