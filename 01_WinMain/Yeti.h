#pragma once
#include "Champ.h"
class Yeti : public Champ
{
public:

	Yeti();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

