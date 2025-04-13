#include "Heroine.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include "PhysicsController.h"

Heroine::Heroine()
{
	m_state = HeroineState::GetIdleState();

	m_rigidBody = PhysicsController::Instance().AddRigidBody(glm::vec2{ 100,200 }, glm::vec2{ 0,0 }, 40);
	m_animations = SpriteSheet::Pool->GetResource();
	m_animations->Load("../Assets/Textures/RockPaperScissors.tga");
	m_animations->SetSize(4, 4, 280, 170);
	m_animations->AddAnimation(EN_AN_IDLE, 0, 0, 8.0f); //Idle
	m_animations->AddAnimation(EN_AN_JUMP_UP_FALL, 0, 4, 8.0f); //Roll
	m_animations->AddAnimation(EN_AN_CROUCH, 4, 4, 8.0f); //Paper
	m_animations->AddAnimation(EN_AN_RUN, 8, 4, 8.0f); //Scissors
	m_animations->AddAnimation(EN_AN_DEATH, 12, 4, 8.0f); //Rock
	m_animations->SetBlendMode(SDL_BLENDMODE_BLEND);
}

Heroine::~Heroine()
{
}

void Heroine::HandleInput(SDL_Event _event, float _deltaTime)
{
	m_state->HandleInput(this, _event);
}

void Heroine::Update(float _deltaTime)
{
	m_state->Update(this, _deltaTime);
}

void Heroine::Render(Renderer* _renderer)
{
	Rect temp = m_srcRect;
	m_srcRect = { unsigned int((temp.X1*11.6)+3),temp.Y1,unsigned int((temp.X2 * 11.6)+2), temp.Y2 };
	glm::vec2 p = m_rigidBody->GetPosition();
	Rect destRect = Rect(p.x, p.y, p.x + 280, p.y + 170);
	_renderer->RenderTexture(m_animations, m_srcRect, destRect,255);
}