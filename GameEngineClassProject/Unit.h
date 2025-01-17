#pragma once
class Unit
{
public:
	Unit() { m_x = 0; m_y = 0; m_lastX = 0; m_lastY = 0; }

	int GetX() { return m_x; }
	int GetY() { return m_y; }
	int GetLastX() { return m_lastX; }
	int GetLastY() { return m_lastY; }

	void MoveTo(int _x, int _y);

private:
	int m_x;
	int m_y;
	int m_lastX;
	int m_lastY;
};

