#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"

class Level : public Resource
{
public:
	Level();
	virtual ~Level();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

private:
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	Unit* m_unit;
	//otehr interesting level members
};
#endif
