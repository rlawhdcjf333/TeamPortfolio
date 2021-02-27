#pragma once
#include "UI.h"
class ChampSelect : public UI
{
	Image *mBackFrame;
	vector<GameObject*> mChampList;
public:
	ChampSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	int SetIndexX();
};

