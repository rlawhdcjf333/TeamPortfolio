#pragma once
#include "UI.h"

class Sponsor :public UI
{
	Image* mImage;

public:

	Sponsor();
	void Init() override;
	void Render(HDC hdc) override;
	void Release() override;
	void Update() override;
};