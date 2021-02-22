#pragma once
#include "GameObject.h"
class StaffSelect : public GameObject
{
	Image* mImage;
public:
	StaffSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

