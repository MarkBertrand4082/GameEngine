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
	void Animate(float _delta);
	SpriteSheet* GetSheet() { return m_spriteSheet; }

	boolean GetMoving() { return m_moving; }
	void SetMoving(boolean _move) 
	{
		m_moving = _move;
	}

	static ObjectPool<Unit>* Pool;


private:
	SoundEffect* m_soundEffect;
	SpriteSheet* m_spriteSheet;
	boolean m_moving;
};

#endif