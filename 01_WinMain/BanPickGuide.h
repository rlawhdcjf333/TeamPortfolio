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
	
	void NextFrame();
	
};

