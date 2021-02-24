#pragma once
#include "UI.h"

class ChampCheck : public UI
{
	Image* mImage;

public:
	ChampCheck();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

