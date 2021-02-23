#pragma once
#include "UI.h"

class ChampInfo :public UI
{
	Image* mImage;


public:

	ChampInfo();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};
