#pragma once
#include "UI.h"
#include "Director.h"

class StaffList : public UI
{

	Image* mImage;
	Director* mDirector;

	vector<Staff*> mStaffList;
public:

	StaffList();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void LoadStaffList();



};