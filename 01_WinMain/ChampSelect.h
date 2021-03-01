#pragma once
#include "UI.h"

enum class SelectState {
	BlueBan,	//0번째 Guide
	RedBan,		//1번째
	BluePick1,	//2번째
	RedPick1,	//3번째
	RedPick2,	//3번째
	BluePick2,	//4번째
	BluePick3,	//4번째
	RedPick3,	//5번째
	end			//6번째
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

	int SetIndexX(GameObject* pt);	//mBackFrame xFrameindex 바꾸려고 만듬, pt : 챔프 포인터
	void NextState();
	void ChampRender(HDC hdc, int x , int y, vector<GameObject*> list, int i);
	void ChampInfoRender(HDC hdc, Champ* champ);
	void BanRender(HDC hdc, int x, int y, Champ* champ);

	void DelayReset() { mDelay = 2.f; }


	void SetState(SelectState state){ mState = state;}
	void ClearCurrentChamp();
};

