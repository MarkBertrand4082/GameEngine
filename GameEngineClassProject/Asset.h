#ifndef ASSET_H
#define ASSET_H

#include "StandardIncludes.h"
#include "ObjectPool.h"

class Asset
{
public:
	Asset();
	virtual ~Asset() {}

	string GetGUID() { return m_GUID; }
	int GetDataSize() { return m_dataSize; }
	void SetDataSize(int _size) { m_dataSize = _size; }
	byte* GetData() { return m_data; }
	void SetData(byte * _data) { m_data = _data; }

	static ObjectPool<Asset>* Pool;

private:
	string m_GUID;
	int m_dataSize;
	byte* m_data;
};
#endif

