#pragma once
#include "UI.h"

class Director;
class StaffSelect : public UI
{
	Image* mImage;

	Director* player;
	Director* enemy;

	int startX;
	int startY;

public:
	StaffSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void RenderStaffList(HDC hdc, int x, int y, int index);
	void RenderWatingList(HDC hdc, int x, int y, int index);

};

