#pragma once
#include "UI.h"
class PickBattleUI;
class StaffSelect : public UI
{
	PickBattleUI* mPickBattleUI;
	vector <RECT> mButtonList;
	Image* mImage;

public:
	StaffSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void SetUIptr(PickBattleUI* ptr) { mPickBattleUI = ptr; }
};

