#pragma once
#include "UI.h"

class Peedback : public UI
{
	Image* mImage;

public:
	Peedback();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

