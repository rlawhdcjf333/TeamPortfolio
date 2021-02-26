#pragma once
#include "UI.h"

class StaffResult;
class Director;
class StaffSearch : public UI
{

	Image* mImage;
	StaffResult* mStaffResult;
	Director* mDirector;

public:

	StaffSearch(int x, int y, Director* dir);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};