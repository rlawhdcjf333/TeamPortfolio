#pragma once
#include "UI.h"

class OperationToggle :public UI
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

