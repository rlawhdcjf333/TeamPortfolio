#pragma once
#include "GameObject.h"

class TeamToggle :public GameObject
{
	Image* mImage;
	// mIsActive 변수가 조상님께 있으니 잘 받아쓰자

public:

	TeamToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

