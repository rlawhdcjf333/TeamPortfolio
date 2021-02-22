#pragma once
#include "UI.h"

class Training : public UI
{

	Image* mImage;

	vector <GameObject*> mStaffList;

public:
	Training();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};