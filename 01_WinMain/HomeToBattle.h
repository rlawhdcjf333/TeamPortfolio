#pragma once
#include "GameObject.h"

class HomeToBattle :public GameObject
{
	vector <RECT> mButtonList;
	Image* mImage;
	// mIsActive 변수가 조상님께 있으니 잘 받아쓰자

public:

	HomeToBattle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void LoadFromFile(const string& fileName);
	void mToggleButton(int index, string UIName);


};

