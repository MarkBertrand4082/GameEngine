#pragma once
class Unit
{
public:
	Unit() { m_x = 0, m_y = 0; }

	int GetX() { return m_x; }
	int GetY() { return m_y; }

	void MoveTo(int _x, int _y);

private:
	int m_x;
	int m_y;
};

