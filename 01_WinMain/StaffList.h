#pragma once
#include "UI.h"

class Staff;
class Director;
class StaffListDetail;
class StaffList : public UI
{

	Image* mImage;
	Director* mDirector;
	StaffListDetail* mStaffListDetail;
	vector<Staff*> mStaffList;

	bool mIsToggleDetail;

public:

	StaffList();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void LoadStaffList();
	void UpdateStaffList();

	int GetStaffSize() { return mStaffList.size(); }
	void SetIsToggleDetail(bool b) { mIsToggleDetail = b; }
};