#pragma once
#include "UI.h"

enum class SelectState {
	BlueBan,	//0��° Guide
	RedBan,		//1��°
	BluePick1,	//2��°
	RedPick1,	//3��°
	RedPick2,	//3��°
	BluePick2,	//4��°
	BluePick3,	//4��°
	RedPick3,	//5��°
	end			//6��°
};

class ChampSelect : public UI
{
	Image *mBackFrame;
	vector<GameObject*> mChampList;
	SelectState mState;
	
	Champ* mCurrentChamp;
	RECT mCurrentRect;

	float mDelay;
	

public:
	ChampSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	GameObject* ChampToggle();

	GameObject* ToggleButton(int index);

	int SetIndexX(GameObject* pt);	//mBackFrame xFrameindex �ٲٷ��� ����, pt : è�� ������
	void NextState();
	void ChampRender(HDC hdc, int x , int y, vector<GameObject*> list, int i);
	void ChampInfoRender(HDC hdc, Champ* champ);
	void BanRender(HDC hdc, int x, int y, Champ* champ);

	void DelayReset() { mDelay = 2.f; }


	void SetState(SelectState state){ mState = state;}
	void ClearCurrentChamp();
};

