#pragma once
#include "Champ.h"
class ZombieMonkey : public Champ
{
public:

	ZombieMonkey(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

