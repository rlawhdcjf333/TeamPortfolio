#pragma once
#include "GameObject.h"

class HomeToBattle :public GameObject
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

