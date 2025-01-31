#ifndef ASSET_CONTROLLER_H
#define ASSET_CONTROLLER_H

#include "StandardIncludes.h"
#include "StackAllocator.h"
#include "Asset.h"

class AssetController : public Singleton<AssetController>
{
public:
	AssetController();
	virtual ~AssetController();

	//Methods
	void Initialize(int _stackSize);
	Asset* GetAsset(string _guid);

	//Members
	static StackAllocator* Stack;

private:
	//Members
	map<string, Asset*> m_assets;
};

#endif