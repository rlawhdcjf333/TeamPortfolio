#pragma once
#include "Champ.h"
class Ranger: public Champ
{
public:

	Ranger();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

