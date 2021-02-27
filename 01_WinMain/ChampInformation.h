#pragma once
#include "UI.h"

class Champ;
class ChampInfo;
class ChampInformation : public UI {

	Image* mImage;

	Champ* mCurrentChamp;
	ChampInfo* mChampInfo;
	vector<Champ*> mChampList;
	vector<RECT> mRectList;
	

public:

	ChampInformation();
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	wstring ClassTypeCheck(Champ* champ);

	void SetCurrentChamp(Champ* champ) { mCurrentChamp = champ; }
	void SetChampList(vector<Champ*> ChampList) { mChampList = ChampList; }
	void SetChampInfo(ChampInfo* champInfo) { mChampInfo = champInfo; }

	void PrevButton();
	void NextButton();
};