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

	while (!m_quit)
	{
		m_timing->Tick();

		m_r->SetDrawColor(Color{ 255,255,255,255 });
		m_r->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}
		m_fArial20->Write(m_r->GetRenderer(), m_name1.c_str(), SDL_Color{ 255,125,0 }, SDL_Point{ 50,65 });
		m_fArial20->Write(m_r->GetRenderer(), m_name2.c_str(), SDL_Color{ 255,125,0 }, SDL_Point{ 50,210 });


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
	m_input->MS()->ProcessButtons(_event);
}