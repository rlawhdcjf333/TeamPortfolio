#pragma once
#include "UI.h"

class StaffList : public UI
{

	Image* mImage;

public:

	StaffList();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;





};