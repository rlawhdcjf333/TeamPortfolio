#pragma once
#include "UI.h"

class Champ;
class ChampSelect : public UI
{
	Image *mBackFrame;
	vector<GameObject*> mChampList;
	
	Champ* mCurrentChamp;
	RECT mCurrentRect;


public:
	ChampSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void ChampRender(HDC hdc, int x , int y, vector<GameObject*> list, int i);

	int SetIndexX();
};

