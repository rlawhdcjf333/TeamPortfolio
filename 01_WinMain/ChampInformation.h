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
	

	wstring mClassChampType;
	wstring mChampName;
	wstring mChampInformation;
	wstring mChampAtk;
	wstring mChampAtkSpeed;
	wstring mChampRange;
	wstring mChampDef;
	wstring mChampHp;
	wstring mChampSpeed;
	wstring mChampEx;
	wstring mSkillCool;
	wstring mSpecialSkillCool;
	wstring mChampSkill;
	wstring mChampSpecialSkill;

	HDC mHdc;

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