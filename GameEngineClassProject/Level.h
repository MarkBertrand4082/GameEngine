#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"

class Renderer;
class AudioController;
class PhysicsController;

class Level : public Resource
{
public:
	Level(Renderer& _r, AudioController& _a, PhysicsController& _p);
	virtual ~Level();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

private:
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	vector<Unit*> m_units;
	Renderer* m_r;
	AudioController* m_a;
	PhysicsController* m_p;
	//otehr interesting level members
};
#endif
