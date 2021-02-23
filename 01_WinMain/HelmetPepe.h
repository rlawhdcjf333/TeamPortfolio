#pragma once
#include "Champ.h"
class HelmetPepe : public Champ
{
public:

	HelmetPepe();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};