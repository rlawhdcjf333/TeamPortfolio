#pragma once
#include "GameObject.h"

class GameToggle :public GameObject
{
	Image* mActive;
	Image* mImage;
	vector <RECT> mButtonList;


public:

	GameToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void mToggleButton(int index, string UIName, function <void(void)> func = []() {});


};
