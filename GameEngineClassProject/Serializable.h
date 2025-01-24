#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "StandardIncludes.h"

class Serializable
{
public:
	Serializable() {}
	virtual ~Serializable() {}
	

	virtual void Serialize(ostream& _stream) = 0;
	virtual void Deserialize(istream& _stream) = 0;
};

#endif