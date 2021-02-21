#pragma once
#include "GameObject.h"

class SystemToggle :public GameObject
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

