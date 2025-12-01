#include "RigidBody.h"

ObjectPool<RigidBody>* RigidBody::Pool;

RigidBody::RigidBody()
{
	Reset();
}

void RigidBody::Reset()
{
	m_position = {};
	m_velocity = {0,0};
	m_acceleration = {0,0};
	m_buoyancy = {0,0};
	m_buoyancyDecay = {0,0};
	m_buoyancyMin = { 0,0 };
	m_randomForce = { 0,0 };
	m_wind = {};
	m_mass = 0;
	m_dead = false;
}

void RigidBody::Update(float _deltaTime, glm::vec2 _force)
{
	_force += m_wind + m_buoyancy + m_randomForce;
	_force.y *= -1;//INvert force cause rendering Y axis is inverted
	m_acceleration = _force * m_mass;
	m_velocity += m_acceleration * _deltaTime;
	m_position += m_velocity * _deltaTime;

	m_buoyancy -= m_buoyancyDecay * _deltaTime;
	m_buoyancy.x = std::fmax(m_buoyancy.x, m_buoyancyMin.x);
	m_buoyancy.y = std::fmax(m_buoyancy.y, m_buoyancyMin.y);
}