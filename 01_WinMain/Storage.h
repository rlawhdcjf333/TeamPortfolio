#pragma once
#include "ObjectManager.h"

class Storage : public ObjectManager 
{
	Singleton(Storage);

public:
	Storage();

};
