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
#include "Unit.h"
#include "SoundEffect.h"
#include "Controller.h"

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
	m_quit = false;
	m_wins1 = 0;
	m_wins2 = 0;
	m_won1 = false;
	m_won2 = false;
	m_mPos = {};
	m_gameTime = 0.0;
	m_saves = 0;
	m_loads = 0;
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
	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	_stream.write(reinterpret_cast<char*>(&m_name1), sizeof(m_name1));
	_stream.write(reinterpret_cast<char*>(&m_name2), sizeof(m_name2));
	_stream.write(reinterpret_cast<char*>(&m_wins1), sizeof(m_wins1));
	_stream.write(reinterpret_cast<char*>(&m_wins2), sizeof(m_wins2));
	_stream.write(reinterpret_cast<char*>(&m_mPos), sizeof(m_mPos));
	_stream.write(reinterpret_cast<char*>(&m_won1), sizeof(m_won1));
	_stream.write(reinterpret_cast<char*>(&m_won2), sizeof(m_won2));
	_stream.write(reinterpret_cast<char*>(&m_quit), sizeof(m_quit));

	SerializePointer(_stream, m_fist1);
	SerializePointer(_stream, m_fist2);

	Resource::Serialize(_stream);
}

void Level2::Deserialize(std::istream& _stream)
{
	_stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	_stream.read(reinterpret_cast<char*>(&m_name1), sizeof(m_name1));
	_stream.read(reinterpret_cast<char*>(&m_name2), sizeof(m_name2));
	_stream.read(reinterpret_cast<char*>(&m_wins1), sizeof(m_wins1));
	_stream.read(reinterpret_cast<char*>(&m_wins2), sizeof(m_wins2));
	_stream.read(reinterpret_cast<char*>(&m_mPos), sizeof(m_mPos));
	_stream.read(reinterpret_cast<char*>(&m_won1), sizeof(m_won1));
	_stream.read(reinterpret_cast<char*>(&m_won2), sizeof(m_won2));
	_stream.read(reinterpret_cast<char*>(&m_quit), sizeof(m_quit));
	DeserializePointer(_stream, m_fist1);
	DeserializePointer(_stream, m_fist2);

	Resource::Deserialize(_stream);
}

void Level2::ToString()
{
	cout << "Level2" << endl;
	Resource::ToString();
}

void Level2::Play()
{
	m_input->CT()->DetectControllers();
	m_fist1 = new Unit();
	m_fist1->AssignNonDefaultValues();
	m_fist2 = new Unit();
	m_fist2->AssignNonDefaultValues();
	m_fist1->GetHeroine()->GetRigidBody()->SetPosition(glm::vec2{ 20,30});
	m_fist2->GetHeroine()->GetRigidBody()->SetPosition(glm::vec2{ 20,330});
	Song* song = m_a->LoadSong("../Assets/Audio/Music/Track1.mp3");
	m_a->Play(song);

	
	while (!m_quit)
	{
		m_timing->Tick();

		m_r->SetDrawColor(Color{ 255,255,255,255 });
		m_r->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}
		
		m_fist1->GetHeroine()->Update(m_timing->GetDeltaTime());
		m_fist2->GetHeroine()->Update(m_timing->GetDeltaTime());
		m_fist1->GetHeroine()->Render(m_r);
		m_fist2->GetHeroine()->Render(m_r);
		m_p->Update(m_timing->GetDeltaTime());
		Win();
		
		m_fArial20->Write(m_r->GetRenderer(), m_name1.c_str(), SDL_Color{ 0,255,0 }, SDL_Point{ int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y) });
		m_fArial20->Write(m_r->GetRenderer(), m_state1.c_str(), SDL_Color{ 255,0,0 }, SDL_Point{ int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y)+20 });
		m_fArial20->Write(m_r->GetRenderer(), ("Wins: " + to_string(m_wins1)).c_str(), SDL_Color{ 0,0,255 }, SDL_Point{ int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y)+40 });
		m_fArial20->Write(m_r->GetRenderer(), ("Losses: " + to_string(m_wins2)).c_str(), SDL_Color{ 0,0,255 }, SDL_Point{ int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y)+60 });

		m_fArial20->Write(m_r->GetRenderer(), m_name2.c_str(), SDL_Color{ 0,255,0 }, SDL_Point{ int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y) });
		m_fArial20->Write(m_r->GetRenderer(), m_state2.c_str(), SDL_Color{ 255,0,0 }, SDL_Point{ int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y)+20 });
		m_fArial20->Write(m_r->GetRenderer(), ("Wins: " + to_string(m_wins2)).c_str(), SDL_Color{ 0,0,255 }, SDL_Point{ int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y)+40 });
		m_fArial20->Write(m_r->GetRenderer(), ("Losses: " + to_string(m_wins1)).c_str(), SDL_Color{ 0,0,255 }, SDL_Point{ int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x),int(m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y)+60 });

		m_gameTime += m_timing->GetDeltaTime();
		m_fArial20->Write(m_r->GetRenderer(), ("Frames Per Second: "+to_string(m_timing->GetFPS()) + "  Game Time: "+to_string(int(m_gameTime)) + "  Saves: " + to_string(m_saves) + "  Loads: "+to_string(m_loads)).c_str(), SDL_Color{0,0,255}, SDL_Point{0,1040});
		m_fArial20->Write(m_r->GetRenderer(), "Quit [ESC]  Next Game State [SPACE]  Save [F5]  Load [F7]", SDL_Color{ 0,0,255 }, SDL_Point{ 0,1060 });
		m_fArial20->Write(m_r->GetRenderer(), m_input->CT()->ToString().c_str(), SDL_Color{0,0,255}, SDL_Point{500,500});

		SDL_RenderPresent(m_r->GetRenderer());

		m_timing->CapFPS();
	}
}

void Level2::HandleInput(SDL_Event _event)
{
	
	string temp;
	m_input->MS()->ProcessButtons(_event);
	if ((_event.type == SDL_QUIT) || (m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	//saving and loading
	else if (m_input->KB()->KeyUp(_event, SDLK_F5))
	{
		m_saves++;
		ofstream writeStream("saveGame.bin", ios::out | ios::binary);
		Serialize(writeStream);
		writeStream.close();
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_F7))
	{
		ifstream readStream("saveGame.bin", ios::in | ios::binary);
		Deserialize(readStream);
		readStream.close();
		m_loads++;
	}
	//Mouse
	else if (m_input->MS()->GetButLDown())
	{
		if (m_input->MS()->Moved(_event, m_mPos))
		{
			m_fist1->GetHeroine()->GetRigidBody()->SetPosition(glm::vec2{ m_mPos.X-140, m_mPos.Y-85 });
		}
	}
	else if (m_input->MS()->GetButRDown())
	{
		if (m_input->MS()->Moved(_event, m_mPos))
		{
			m_fist2->GetHeroine()->GetRigidBody()->SetPosition(glm::vec2{ m_mPos.X-140, m_mPos.Y-85 });
		}
	}
	//arrow keys
	else if (m_input->KB()->KeyDown(_event, SDLK_UP))
	{
		m_fist2->GetHeroine()->GetRigidBody()->SetPosition({ m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x, m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y -=10});
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN))
	{
		m_fist2->GetHeroine()->GetRigidBody()->SetPosition({ m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x, m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y +=10});
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT))
	{
		m_fist2->GetHeroine()->GetRigidBody()->SetPosition({ m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x-=10, m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y });
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT))
	{
		m_fist2->GetHeroine()->GetRigidBody()->SetPosition({ m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x+=10, m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y });
	}
	//WASD
	else if (m_input->KB()->KeyDown(_event, SDLK_w))
	{
		m_fist1->GetHeroine()->GetRigidBody()->SetPosition({ m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x, m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y -= 10 });
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_s))
	{
		m_fist1->GetHeroine()->GetRigidBody()->SetPosition({ m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x, m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y += 10 });
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_a))
	{
		m_fist1->GetHeroine()->GetRigidBody()->SetPosition({ m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x -= 10, m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y });
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_d))
	{
		m_fist1->GetHeroine()->GetRigidBody()->SetPosition({ m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x += 10, m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y });
	}

	//Controller
	else if (m_input->CT()->ProcessMotion(_event))
	{
		m_fist1->GetHeroine()->GetRigidBody()->SetPosition({ m_fist1->GetHeroine()->GetRigidBody()->GetPosition().x += m_input->CT()->GetControllers()[0].LeftAxis.X%20, m_fist1->GetHeroine()->GetRigidBody()->GetPosition().y += m_input->CT()->GetControllers()[0].LeftAxis.Y%20 });
		m_fist2->GetHeroine()->GetRigidBody()->SetPosition({ m_fist2->GetHeroine()->GetRigidBody()->GetPosition().x += m_input->CT()->GetControllers()[0].RightAxis.X%20, m_fist2->GetHeroine()->GetRigidBody()->GetPosition().y += m_input->CT()->GetControllers()[0].RightAxis.Y%20 });
	}


	m_fist1->GetHeroine()->HandleInput(_event, m_timing->GetDeltaTime());
	m_fist2->GetHeroine()->HandleInput(_event, m_timing->GetDeltaTime());
	
}

void Level2::Win()
{
	if (m_fist1->GetHeroine()->GetState() == HeroineState::GetIdleState() && m_fist2->GetHeroine()->GetState() == HeroineState::GetIdleState())
	{
		m_state1 = "Waiting to start...";
		m_state2 = "Waiting to start...";
	}
	else if (m_fist1->GetHeroine()->GetState() == HeroineState::GetRollState() && m_fist2->GetHeroine()->GetState() == HeroineState::GetRollState())
	{
		m_state1 = "Rolling...";
		m_state2 = "Rolling...";
		m_won1 = false;
		m_won2 = false;
	}
	else if (m_fist1->GetHeroine()->GetState() == HeroineState::GetPaperState())
	{
		if (m_fist2->GetHeroine()->GetState() == HeroineState::GetScissorsState())
		{
			m_state1 = "LOSER!";
			m_state2 = "WINNER!";
			if (!m_won2)
			{
				m_wins2 += 1;
				m_won2 = true;
			}
		}
		else if (m_fist2->GetHeroine()->GetState() == HeroineState::GetRockState())
		{
			m_state1 = "WINNER!";
			m_state2 = "LOSER!";
			if (!m_won1)
			{
				m_wins1 += 1;
				m_won1 = true;
			}
		}
		else if (m_fist2->GetHeroine()->GetState() == HeroineState::GetPaperState())
		{
			m_state1 = "DRAW!";
			m_state2 = "DRAW!";
		}
	}
	else if (m_fist1->GetHeroine()->GetState() == HeroineState::GetScissorsState())
	{
		if (m_fist2->GetHeroine()->GetState() == HeroineState::GetRockState())
		{
			m_state1 = "LOSER!";
			m_state2 = "WINNER!";
			if (!m_won2)
			{
				m_wins2 += 1;
				m_won2 = true;
			}
		}
		else if (m_fist2->GetHeroine()->GetState() == HeroineState::GetPaperState())
		{
			m_state1 = "WINNER!";
			m_state2 = "LOSER!";
			if (!m_won1)
			{
				m_wins1 += 1;
				m_won1 = true;
			}
		}
		else if (m_fist2->GetHeroine()->GetState() == HeroineState::GetScissorsState())
		{
			m_state1 = "DRAW!";
			m_state2 = "DRAW!";
		}
	}
	else if (m_fist1->GetHeroine()->GetState() == HeroineState::GetRockState())
	{
		if (m_fist2->GetHeroine()->GetState() == HeroineState::GetPaperState())
		{
			m_state1 = "LOSER!";
			m_state2 = "WINNER!";
			if (!m_won2)
			{
				m_wins2 += 1;
				m_won2 = true;
			}
		}
		else if (m_fist2->GetHeroine()->GetState() == HeroineState::GetScissorsState())
		{
			m_state1 = "WINNER!";
			m_state2 = "LOSER!";
			if (!m_won1)
			{
				m_wins1 += 1;
				m_won1 = true;
			}
		}
		else if (m_fist2->GetHeroine()->GetState() == HeroineState::GetRockState())
		{
			m_state1 = "DRAW!";
			m_state2 = "DRAW!";
		}
	}
}