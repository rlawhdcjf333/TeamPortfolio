#pragma once
#include "UI.h"

class HomeToBattle :public UI
{
	Image* mImage;
	// mIsActive ������ ����Բ� ������ �� �޾ƾ���

public:

	HomeToBattle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

