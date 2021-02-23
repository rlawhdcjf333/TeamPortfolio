#pragma once
#include "UI.h"

class StaffSelect : public UI
{
	Image* mImage;

public:
	StaffSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

