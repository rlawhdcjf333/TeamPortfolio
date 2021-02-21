#pragma once
#include "GameObject.h"

class LeagueToggle :public GameObject
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

