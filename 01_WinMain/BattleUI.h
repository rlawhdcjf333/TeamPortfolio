#pragma once
#include "UI.h"

class Director;
class BattleUI : public UI
{
	Image* mImage;
	Image* mWinImage;
	int mTime;
	float mDeltaTime;

	Director* mPlayer;
	Director* mEnemy;

public:
	BattleUI();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void StaffInfoRender(HDC hdc);
	void DrawStaff(HDC hdc, int x, int y, vector<Staff*> list, int i);
	void TeamRender(HDC hdc);

};
