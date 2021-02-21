#pragma once
#include "GameObject.h"

class OperationToggle :public GameObject
{
	Image* mActive;
	Image* mImage;

public:

	OperationToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

