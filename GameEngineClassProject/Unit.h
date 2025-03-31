#ifndef UNIT_H
#define UNIT_H

#include "Resource.h"
#include "SoundEffect.h"
#include "SpriteSheet.h"

class Unit : public Resource
{
public:
	Unit();
	virtual ~Unit();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	SpriteSheet* GetSheet() { return m_spriteSheet; }

	static ObjectPool<Unit>* Pool;

private:
	glm::vec2 m_direction;
	SoundEffect* m_soundEffect;
	SpriteSheet* m_spriteSheet;
};

#endif