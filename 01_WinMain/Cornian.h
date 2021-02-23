#pragma once
#include "Champ.h"
class Cornian : public Champ
{
public:

	Cornian();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
