#pragma once
#include "UI.h"

class Staff;
class StaffList;
class Training;
class Director;
class StaffListDetail : public UI {

	Image* mImage;
	Staff* mCurrentStaff;
	StaffList* mStaffList;
	Training* mTraining;
	Director* mDirector;

	bool mIsAlertOn;
	float mDuration;

public:

	StaffListDetail();
	void Init()override;
	void Render(HDC hdc)override;
	void Update()override;
	void Release()override;

	void SetStaff(Staff* currentStaff) { mCurrentStaff = currentStaff; }
	void SetStaffList(StaffList* staffList) { mStaffList = staffList; }
};