#pragma once
#include "UI.h"

class LeagueToggle :public UI
{
	Image* mActive;
	Image* mImage;

public:

	LeagueToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

