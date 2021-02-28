#pragma once
#include "UI.h"
class BattleUI : public UI
{
	Image* mImage;
	int mTime;
	float mDeltaTime;
public:
	BattleUI();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void StaffInfoRender(HDC hdc);
	void DrawStaff(HDC hdc, int x, int y, vector<Staff*> list, int i);

};
