#pragma once
#include "UI.h"

class TeamToggle :public UI
{
	Image* mActive;
	Image* mImage;
	// mIsActive ������ ����Բ� ������ �� �޾ƾ���

public:

	TeamToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

