#pragma once
#include "UI.h"
class OnPatch : public UI
{
	Image* mImage;
	float mDuration;
	float mCurrentTime;

public:

	OnPatch(const string& name);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

};

