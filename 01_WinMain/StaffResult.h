#pragma once
#include "UI.h"

class Staff;
class Director;
class StaffSearch;
class StaffList;
class Training;

class StaffResult : public UI
{

	Image* mImage;

	Director* mDirector;
	Staff* mStaff;
	StaffList* mStaffList;
	Training* mTraining;

	int mCost;

public:

	StaffResult(int x, int y, Director* dir);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};