#ifndef UNIT_H
#define UNIT_H

#include "Resource.h"
#include "SoundEffect.h"

class Unit : public Resource
{
public:
	Unit();
	virtual ~Unit();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;


	//Member
	static ObjectPool<Unit>* Pool;

private:
	SoundEffect* m_soundEffect;
};

#endif