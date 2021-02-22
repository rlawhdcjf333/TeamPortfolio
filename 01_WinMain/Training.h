#pragma once
#include "UI.h"
#include "Staff.h"

class Training : public UI
{

	Image* mImage;

	vector <GameObject*> mStaffList;

	Staff* mCurrentStaff;
	wstring mCurrentStaffName;
	int mCurrentStaffAtk;
	int mCurrentStaffDef;

public:
	Training();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void LoadStaffList();
	void RenderCurrentStaff(HDC hdc);
	void DrawStaffList(HDC hdc, int i);
};