#pragma once
#include "Champ.h"
class BabyMonkey : public Champ
{
public:

	BabyMonkey(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
