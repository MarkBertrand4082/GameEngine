#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{
	m_soundEffect = nullptr;
	m_spriteSheet = nullptr;
	m_direction = { 0,0 };

}

Unit::~Unit()
{
}

void Unit::AssignNonDefaultValues()
{
	m_soundEffect = SoundEffect::Pool->GetResource();
	m_soundEffect->AssignNonDefaultValues();
	m_spriteSheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
	m_spriteSheet->AddAnimation(EN_AN_RUN, 0, 6, 6.0f);
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