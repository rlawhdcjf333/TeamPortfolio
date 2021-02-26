#pragma once
#include "UI.h"

class Director;
class StaffSearch;
class NewStaff : public UI
{

	Image* mImage;
	Director* mDirector;

	vector <StaffSearch*> mStaffSearchList;

public:

	NewStaff();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};