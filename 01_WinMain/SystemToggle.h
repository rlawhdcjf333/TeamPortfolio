#pragma once
#include "UI.h"

class SystemToggle :public UI
{
	Image* mActive;
	Image* mImage;

public:

	SystemToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

