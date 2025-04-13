#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{
	m_hero = nullptr;
}

Unit::~Unit()
{
}


void Unit::AssignNonDefaultValues()
{
	m_hero = new Heroine();
	m_hero->GetRigidBody()->SetMass(0.0f);
	Resource::AssignNonDefaultValues();
}

void Unit::Serialize(std::ostream & _stream)
{
	auto temp = &m_hero->GetRigidBody()->GetPosition();
	_stream.write(reinterpret_cast<char*>(temp), sizeof(temp));


	Resource::Serialize(_stream);
}

void Unit::Deserialize(std::istream& _stream)
{
	AssignNonDefaultValues();
	auto temp = &m_hero->GetRigidBody()->GetPosition();
	_stream.read(reinterpret_cast<char*>(temp), sizeof(temp));

	m_hero->GetRigidBody()->SetPosition(*temp);
	
	Resource::Deserialize(_stream);
}

void Unit::ToString()
{
	cout << "UNIT" << endl;
	Resource::ToString();
}