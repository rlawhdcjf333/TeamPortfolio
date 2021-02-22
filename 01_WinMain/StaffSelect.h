#pragma once
#include "GameObject.h"
class StaffSelect : public GameObject
{
	vector <RECT> mButtonList;
	Image* mImage;

public:
	StaffSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void LoadFromFile(const string& fileName);
	void mToggleButton(int index, string UIName);
};

