#pragma once
#include "UI.h"

class NewStaff;
class TeamToggle :public UI
{
	Image* mActive;
	Image* mImage;
	// mIsActive 변수가 조상님께 있으니 잘 받아쓰자
	NewStaff* mNewStaff;

public:

	TeamToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

