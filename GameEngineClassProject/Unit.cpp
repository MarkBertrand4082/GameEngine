#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{
	m_soundEffect = nullptr;
	m_spriteSheet = nullptr;
	m_moving = false;
	m_flip = false;
	m_dir = { 0,0 };
}

Unit::~Unit()
{
}

void Unit::Animate(float _delta)
{
	m_spriteSheet->Update(EN_AN_RUN, _delta);
}

void Unit::AssignNonDefaultValues()
{
	m_soundEffect = SoundEffect::Pool->GetResource();
	m_soundEffect->AssignNonDefaultValues();


	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();

	m_spriteSheet = SpriteSheet::Pool->GetResource();
	m_spriteSheet->Load("../Assets/Textures/Warrior.tga");
	m_spriteSheet->SetSize(17, 6, 69, 44);
	m_spriteSheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
	m_spriteSheet->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);
	Resource::AssignNonDefaultValues();
}

void Unit::Serialize(std::ostream & _stream)
{
	SerializePointer(_stream, m_soundEffect);
	SerializePointer(_stream, m_spriteSheet);
	Resource::Serialize(_stream);
}

void Unit::Deserialize(std::istream& _stream)
{
	DeserializePointer(_stream, m_soundEffect);
	DeserializePointer(_stream, m_spriteSheet);
	Resource::Deserialize(_stream);
}

void Unit::ToString()
{
	cout << "UNIT" << endl;
	m_soundEffect->ToString();
	m_spriteSheet->ToString();
	Resource::ToString();
}