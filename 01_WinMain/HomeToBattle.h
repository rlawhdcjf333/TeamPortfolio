#pragma once
#include "GameObject.h"

class HomeToBattle :public GameObject
{
	vector <RECT> mButtonList;
	Image* mImage;
	// mIsActive ������ ����Բ� ������ �� �޾ƾ���

public:

	HomeToBattle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void LoadFromFile(const string& fileName);
	void mToggleButton(int index, string UIName);


};

