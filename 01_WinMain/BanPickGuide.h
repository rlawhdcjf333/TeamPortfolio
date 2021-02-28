#pragma once
#include "UI.h"

class BanPickGuide : public UI
{
	Image* mImage;
	int mFrameY;
public:
	BanPickGuide();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	
	void NextFrame() {
		if(mIsActive)
			mFrameY++;
		if (mFrameY >= 6)
		{
			mFrameY = 0;
			mIsActive = false;
			ObjectManager::GetInstance()->FindObject("ChampSelect")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("ChampCheck")->SetIsActive(true);
		}
	}
};

