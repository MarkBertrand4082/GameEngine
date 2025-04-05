#ifndef PHYSICSCONTROLLER_H
#define PHYSICSCONTROLLER_H

#include "StandardIncludes.h"
#include "Particle.h"

class Renderer;

class PhysicsController : public Singleton<PhysicsController>
{
public:
	PhysicsController();
	virtual ~PhysicsController() {}

	float GetGravity() { return m_gravity; }
	void SetGravity(float _gravity) { m_gravity = _gravity; }
	vector<Particle*>& GetParticles() { return m_particles; }

	void Update(float _deltaTime);
	Particle* AddParticle(glm::vec2 _position, float _lifeTime);
	string ToString();

private:
	float m_gravity;
	glm::vec2 m_force;
	vector<Particle*> m_particles;
};

#endif