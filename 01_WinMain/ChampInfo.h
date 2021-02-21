#pragma once
#include "GameObject.h"

class ChampInfo :public GameObject
{
	Image* mImage;
	vector <RECT> mButtonList;


public:

	ChampInfo();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void mToggleButton(int index, string UIName, function <void(void)> func = []() {});

	void LoadFromFile(const string& fileName);

};
