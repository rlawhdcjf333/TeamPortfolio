#pragma once
#include "GameObject.h"

class TeamToggle :public GameObject
{
	Image* mImage;
	// mIsActive ������ ����Բ� ������ �� �޾ƾ���

public:

	TeamToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

