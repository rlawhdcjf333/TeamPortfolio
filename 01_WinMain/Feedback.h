#pragma once
#include "UI.h"

class Feedback : public UI
{
	Image* mImage;

public:
	Feedback();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

