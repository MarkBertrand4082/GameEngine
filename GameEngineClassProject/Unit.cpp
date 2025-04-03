#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{
	m_soundEffect = nullptr;
	m_spriteSheet = nullptr;
	m_moving = false;
	m_flip = false;
	m_dir = { 0,0 };
	m_loc = { 0,0 };
	m_X1 = 0;
	m_X2 = 0;
	m_Y1 = 0;
	m_Y2 = 0;
	m_caught = false;
	m_dead = false;
	m_speed = 0.0;
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
	m_spriteSheet->AddAnimation(EN_AN_DEATH, 27, 11, 6.0f);
	Resource::AssignNonDefaultValues();
}

void Unit::Serialize(std::ostream & _stream)
{
	_stream.write(reinterpret_cast<char*>(&m_moving), sizeof(m_moving));
	_stream.write(reinterpret_cast<char*>(&m_flip), sizeof(m_flip));
	_stream.write(reinterpret_cast<char*>(&m_dir), sizeof(m_dir));
	_stream.write(reinterpret_cast<char*>(&m_loc), sizeof(m_loc));
	_stream.write(reinterpret_cast<char*>(&m_X1), sizeof(m_X1));
	_stream.write(reinterpret_cast<char*>(&m_X2), sizeof(m_X2));
	_stream.write(reinterpret_cast<char*>(&m_Y1), sizeof(m_Y1));
	_stream.write(reinterpret_cast<char*>(&m_Y2), sizeof(m_Y2));
	_stream.write(reinterpret_cast<char*>(&m_caught), sizeof(m_caught));
	_stream.write(reinterpret_cast<char*>(&m_dead), sizeof(m_dead));
	_stream.write(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
	SerializePointer(_stream, m_soundEffect);
	SerializePointer(_stream, m_spriteSheet);

	Resource::Serialize(_stream);
}

void Unit::Deserialize(std::istream& _stream)
{
	_stream.read(reinterpret_cast<char*>(&m_moving), sizeof(m_moving));
	_stream.read(reinterpret_cast<char*>(&m_flip), sizeof(m_flip));
	_stream.read(reinterpret_cast<char*>(&m_dir), sizeof(m_dir));
	_stream.read(reinterpret_cast<char*>(&m_loc), sizeof(m_loc));
	_stream.read(reinterpret_cast<char*>(&m_X1), sizeof(m_X1));
	_stream.read(reinterpret_cast<char*>(&m_X2), sizeof(m_X2));
	_stream.read(reinterpret_cast<char*>(&m_Y1), sizeof(m_Y1));
	_stream.read(reinterpret_cast<char*>(&m_Y2), sizeof(m_Y2));
	_stream.read(reinterpret_cast<char*>(&m_caught), sizeof(m_caught));
	_stream.read(reinterpret_cast<char*>(&m_dead), sizeof(m_dead));
	_stream.read(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
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