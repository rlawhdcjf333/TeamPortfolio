#pragma once
#include "ObjectManager.h"

class Storage : public ObjectManager 
{
	Singleton(Storage);

public:
	Storage();

	void Clear();
	void CopyToStorage(map <ObjectLayer, vector <GameObject*>> list);


	void ElemSwap(ObjectLayer layerName, GameObject* origin);
};
