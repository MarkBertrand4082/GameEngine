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
	void SetMoving(boolean _move) {m_moving = _move;}
	boolean GetFlip() { return m_flip; }
	void SetFlip(boolean _flip) {m_flip = _flip;}
	glm::vec2 GetDir() { return m_dir; }
	void SetDir(glm::vec2 _dir) { m_dir = _dir; }

	int GetX1() { return m_X1; }
	void SetX1(int _x1) { m_X1 = _x1; }
	int GetY1() { return m_Y1; }
	void SetY1(int _y1) { m_Y1 = _y1; }
	int GetX2() { return m_X2; }
	void SetX2(int _x2) { m_X2 = _x2; }
	int GetY2() { return m_Y2; }
	void SetY2(int _y2) { m_Y2 = _y2; }

	static ObjectPool<Unit>* Pool;


private:
	SoundEffect* m_soundEffect;
	SpriteSheet* m_spriteSheet;
	boolean m_moving;
	boolean m_flip;
	int m_X1;
	int m_Y1;
	int m_X2;
	int m_Y2;
	glm::vec2 m_dir;
};

#endif