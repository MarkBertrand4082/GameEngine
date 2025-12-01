#include "HeroineState.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Heroine.h"
#include "SpriteSheet.h"


IdleState HeroineState::m_idle;
RollState HeroineState::m_roll;
PaperState HeroineState::m_paper;
ScissorsState HeroineState::m_scissors;
RockState HeroineState::m_rock;

void IdleState::HandleInput(Heroine* _heroine, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_heroine->SetState(HeroineState::GetRollState());
	}

}

void IdleState::Update(Heroine* _heroine, float _deltaTime)
{
	_heroine->GetAnimations()->Update(EN_AN_IDLE, _deltaTime, _heroine->GetSrcRect());
}


void RollState::HandleInput(Heroine* _heroine, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		int choice = rand() % 3;
		switch (choice)
		{
		case 0:
			_heroine->SetState(HeroineState::GetPaperState());
			break;
		case 1:
			_heroine->SetState(HeroineState::GetScissorsState());
			break;
		case 2:
			_heroine->SetState(HeroineState::GetRockState());
			break;
		}
	}
}

void RollState::Update(Heroine* _heroine, float _deltaTime)
{
	_heroine->GetAnimations()->Update(EN_AN_JUMP_UP_FALL, _deltaTime, _heroine->GetSrcRect());
}

void PaperState::HandleInput(Heroine* _heroine, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_heroine->GetAnimations()->ResetCurrentClip(EN_AN_CROUCH);
		_heroine->SetState(HeroineState::GetIdleState());
	}
}

void PaperState::Update(Heroine* _heroine, float _deltaTime)
{
	_heroine->GetAnimations()->Update(EN_AN_CROUCH, _deltaTime, _heroine->GetSrcRect());
	
}

void ScissorsState::HandleInput(Heroine* _heroine, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_heroine->GetAnimations()->ResetCurrentClip(EN_AN_RUN);
		_heroine->SetState(HeroineState::GetIdleState());
	}
}

void ScissorsState::Update(Heroine* _heroine, float _deltaTime)
{
	_heroine->GetAnimations()->Update(EN_AN_RUN, _deltaTime, _heroine->GetSrcRect());

}

void RockState::HandleInput(Heroine* _heroine, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_heroine->GetAnimations()->ResetCurrentClip(EN_AN_JUMP_UP_FALL);
		_heroine->SetState(HeroineState::GetIdleState());
	}
}

void RockState::Update(Heroine* _heroine, float _deltaTime)
{
	_heroine->GetAnimations()->Update(EN_AN_DEATH, _deltaTime, _heroine->GetSrcRect());
}