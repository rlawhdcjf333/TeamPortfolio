#pragma once
#include "UI.h"

class GameToggle :public UI
{
	Image* mActive;
	Image* mImage;


public:

	GameToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};
