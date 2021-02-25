#pragma once
#include "UI.h"

class Staff;
class TrainingDetail :public UI
{

	Image* mImage;
	Staff* mCurrentStaff;

	typedef map<string, int> ::iterator mapIter;

	int originAtk;
	int originDef;
	int originPoint;

public:
	TrainingDetail();

	void Init()override;
	void Render(HDC hdc)override;
	void Update() override;
	void Release()override;

	void SetStaff(Staff* currentStaff );
	void RenderStaffInfo(HDC hdc);

};

