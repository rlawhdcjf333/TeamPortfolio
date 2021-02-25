#pragma once
#include "UI.h"

class BanPick : public UI
{
	Image* mImage;
	string mNowState;
public:
	BanPick();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

