#pragma once
#include "UI.h"

class Director;
class StaffSelect : public UI
{
	Image* mImage;

	Director* player;
	Director* enemy;

	Staff* firstClick;
	Staff* secondClick;

	RECT firstClickRect;
	RECT secondClickRect;

public:
	StaffSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void DrawStaff(HDC  hdc, int x, int y, vector<Staff*> list, int i);

};

