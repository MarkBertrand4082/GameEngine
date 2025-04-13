#include "Level.h"
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

Level::Level(Renderer* _r, AudioController* _a, PhysicsController* _p, InputController* _i, Timing* _t, TTFont* _font)
{
	AssetController::Instance().Initialize(10000000);
	Unit::Pool = new ObjectPool<Unit>();
	SoundEffect::Pool = new ObjectPool<SoundEffect>();
	m_sdlEvent = {};
	m_r = _r;
	m_a = _a;
	m_p = _p;
	m_input = _i;
	m_timing = _t;
	m_fArial20 = _font;
	m_fArial40 = new TTFont();
	m_fArial40->Initialize(40);
	m_text = "";
	m_text1Done = false;

	m_gameTime = 0.0f;
}

Level::~Level()
{
	delete m_fArial40;
	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues()
{
	m_gameTime = 101.5f;


	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream)
{
	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	

	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream)
{
	_stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	
	Resource::Deserialize(_stream);
}

void Level::ToString()
{
	cout << "LEVEL" << endl;
	cout << "GameTime: " << m_gameTime << endl;
	Resource::ToString();
}

void Level::Play()
{

	Texture::Pool = new ObjectPool<Texture>();
	Texture* texture = Texture::Pool->GetResource();
	texture->Load("../Assets/Textures/Background.tga");
	while (!m_quit && !m_text2Done)
	{
		m_timing->Tick();
		
		m_r->SetDrawColor(Color{255,255,255,255});
		m_r->ClearScreen();
		m_r->RenderTexture(texture, Point(0,0));
	
		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}
		m_fArial40->Write(m_r->GetRenderer(), m_text.c_str(), SDL_Color{255,125,0}, SDL_Point{50,65});
		m_fArial40->Write(m_r->GetRenderer(), m_text2.c_str(), SDL_Color{ 255,125,0 }, SDL_Point{ 50,210 });
		m_fArial20->Write(m_r->GetRenderer(), "Quit [ESC]  Next Nickname [RETURN]", SDL_Color{ 255,255,255 }, SDL_Point{ 0,1060 });
		

		SDL_RenderPresent(m_r->GetRenderer());

		//m_timing->CapFPS();
	}
	delete texture;
}

void Level::HandleInput(SDL_Event _event)
{
	string temp;
	if ((_event.type == SDL_QUIT) || (m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	else if (!m_text1Done)
	{
		if ((temp = m_input->KB()->TextInput(_event)) != "")
		{
			m_text += temp;
		}
		else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_RETURN))
		{
			if (m_text.length() == 0)
			{
				m_text = "No text entered";
			}
			else if (m_text.length() > 21)
			{
				m_text = "Text too long";
			}
			else
			{
				m_text1Done = true;
			}
		}
		else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_BACKSPACE))
		{
			if (m_text.length() > 0)
			{
				m_text.pop_back();
			}
		}
	}
	else {
		if ((temp = m_input->KB()->TextInput(_event)) != "")
		{
			m_text2 += temp;
		}
		else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_RETURN))
		{
			if (m_text2.length() == 0)
			{
				m_text2 = "No text entered";
			}
			else if (m_text2.length() > 21)
			{
				m_text2 = "Text too long";
			}
			else
			{
				m_text2Done = true;
			}
		}
		else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_BACKSPACE))
		{
			if (m_text2.length() > 0)
			{
				m_text2.pop_back();
			}
		}
	}
	m_input->MS()->ProcessButtons(_event);
}