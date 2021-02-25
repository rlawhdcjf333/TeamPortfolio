#pragma once
#include "UI.h"

class Staff;
class Director;
class TrainingDetail;

class Training : public UI
{

	Image* mImage;

	vector <GameObject*> mStaffList;

	Director* mDirector;

	Staff* mSelectedStaff;
	RECT mSelection;

	Staff* mCurrentStaff;
	TrainingDetail* mTrainingDetail;

	wstring mCurrentStaffName;
	int mCurrentStaffAtk;
	int mCurrentStaffDef;
	int mCurrentStaffTrainingPoint;

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