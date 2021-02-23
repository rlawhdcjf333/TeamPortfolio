#pragma once
#include "Champ.h"
class MistKnight : public Champ
{
public:

	MistKnight();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};