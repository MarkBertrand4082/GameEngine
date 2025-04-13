#ifndef UNIT_H
#define UNIT_H

#include "Resource.h"
#include "SoundEffect.h"
#include "SpriteSheet.h"
#include "Heroine.h"

class Heroine;

class Unit : public Resource
{
public:
	Unit();
	virtual ~Unit();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	
	Heroine* GetHeroine() { return m_hero; }

	static ObjectPool<Unit>* Pool;


private:
	Heroine* m_hero;
};

#endif