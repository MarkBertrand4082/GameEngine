#include <iostream>

#include "Unit.h"

void Unit::MoveTo(int _x, int _y) {

	m_x = _x;
	m_y = _y;
	std::cout << "Move To x:" << m_x << " y:" << m_y << "\n";
};