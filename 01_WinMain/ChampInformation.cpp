#include "pch.h"
#include "ChampInformation.h"
#include "Champ.h"
#include "ChampInfo.h"

ChampInformation::ChampInformation()
	:UI("ChampInfomation")
{
	mIsActive = false;
}

void ChampInformation::Init()
{
	LoadFromFile("ChampInformation");

	IMAGEMANAGER->LoadFromFile(L"ChampInformation", Resources(L"ChampInformation.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"ChampInformation");

	mRectList.push_back(RectMakeCenter(WINSIZEX / 2, 92, 412, 42)); // ~ 챔프 상세 설명
	mRectList.push_back(RectMake(50, 242, 190, 200));	// 챔프 이미지
	mRectList.push_back(RectMakeCenter(145, 217, 120, 26));	// 챔프 타입
	mRectList.push_back(RectMake(47, 456, 195, 58));	// 챔프 이름

	for (int i = 0; i < 6; i++) {	// 챔프 능력치
		mRectList.push_back(RectMake(390, 212 + (i * 26), 46, 26));
	}

	mRectList.push_back(RectMake(456, 212, 370, 154));	// 챔프 설명
	
	for (int i = 0; i < 2; i++) {	// 챔프 스킬 아이콘 이미지
		mRectList.push_back(RectMake(284, 390 + (i * 70), 48, 48));
	}

	for (int i = 0; i < 2; i++) {	// 챔프 스킬 쿨
		mRectList.push_back(RectMake(360, 417 + (i * 70), 74, 20));
	}

	for (int i = 0; i < 2; i++) {	// 챔프 스킬 설명
		mRectList.push_back(RectMake(442, 386 + (i * 70), 388, 58));
	}

	// 통계는 없습니다

}

void ChampInformation::Release()
{

}

void ChampInformation::Update()
{
	if (mIsActive) {
		if (Input::GetInstance()->GetKeyDown('Q')) PrevButton();
		if (Input::GetInstance()->GetKeyDown('E')) NextButton();

		auto func = [this]() {	mIsActive = false; };
		auto prevButton = [this]() { PrevButton(); };
		auto nextButton = [this]() { NextButton(); };

		mToggleButton(0, "None", prevButton);
		mToggleButton(1, "None", nextButton);
		mToggleButton(2, "None", func);

		mClassChampType = ClassTypeCheck(mCurrentChamp);
		mChampName = mCurrentChamp->GetChampName();
		mChampInformation = mChampName + L" 상세 정보";
		mChampAtk = to_wstring((int)mCurrentChamp->GetAtk());
		mChampAtkSpeed = to_wstring(0);
		mChampRange = to_wstring(mCurrentChamp->GetRange());
		mChampDef = to_wstring(mCurrentChamp->GetDef());
		mChampHp = to_wstring(mCurrentChamp->GetHP());
		mChampSpeed = to_wstring(mCurrentChamp->GetSpeed());
		mChampEx = mCurrentChamp->GetChampEx();
		mSkillCool = to_wstring(mCurrentChamp->GetSkillCool());
		mSpecialSkillCool = to_wstring(mCurrentChamp->GetSpecialSkillCool());
		mChampSkill = mCurrentChamp->GetSkillEx();
		mChampSpecialSkill = mCurrentChamp->GetSpecialSkillEx();
	}
}

void ChampInformation::Render(HDC hdc)
{
	if (mIsActive) {
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);

		mCurrentChamp->ChampImageRender(hdc, mRectList[1]);
		mCurrentChamp->SkillImageRender(hdc, mRectList[11]);
		mCurrentChamp->SpecialSkillImageRender(hdc, mRectList[12]);
		
		mHdc = hdc;

		function<void(void)> champInformation = [this]() { DrawText(mHdc, mChampInformation.c_str(), mChampInformation.length(), &mRectList[0], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champClassType = [this]() { DrawText(mHdc, mClassChampType.c_str(), mClassChampType.length(), &mRectList[2], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champName = [this]() { DrawText(mHdc, mChampName.c_str(), mChampName.length(), &mRectList[3], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champAtk = [this]() { DrawText(mHdc, mChampAtk.c_str(), mChampAtk.length(), &mRectList[4], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champAtkSpeed = [this]() { DrawText(mHdc, mChampAtkSpeed.c_str(), mChampAtkSpeed.length(), &mRectList[5], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champRange = [this]() { DrawText(mHdc, mChampRange.c_str(), mChampRange.length(), &mRectList[6], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champDef = [this]() { DrawText(mHdc, mChampDef.c_str(), mChampDef.length(), &mRectList[7], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champHp = [this]() { DrawText(mHdc, mChampHp.c_str(), mChampHp.length(), &mRectList[8], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champSpeed = [this]() { DrawText(mHdc, mChampSpeed.c_str(), mChampSpeed.length(), &mRectList[9], DT_VCENTER | DT_CENTER | DT_SINGLELINE); };
		function<void(void)> champEx = [this]() { DrawText(mHdc, mChampEx.c_str(), mChampEx.length(), &mRectList[10], DT_TOP | DT_LEFT | DT_WORDBREAK); };

		function<void(void)> SkillCool = [this]() { DrawText(mHdc, mSkillCool.c_str(), mSkillCool.length(), &mRectList[13], DT_VCENTER | DT_LEFT | DT_SINGLELINE); };
		function<void(void)> SpecialSkillColl = [this]() { DrawText(mHdc, mSpecialSkillCool.c_str(), mSpecialSkillCool.length(), &mRectList[14], DT_VCENTER | DT_LEFT | DT_SINGLELINE); };
		function<void(void)> SkillEx = [this]() { DrawText(mHdc, mChampSkill.c_str(), mChampSkill.length(), &mRectList[15], DT_TOP | DT_LEFT | DT_WORDBREAK); };
		function<void(void)> SpecialSkillEx = [this]() { DrawText(mHdc, mChampSpecialSkill.c_str(), mChampSpecialSkill.length(), &mRectList[16], DT_TOP | DT_LEFT | DT_WORDBREAK); };

		CallFont(hdc, 40, champInformation);
		CallFont(hdc, 20, champClassType);
		CallFont(hdc, 30, champName);
		CallFont(hdc, 15, champAtk);
		CallFont(hdc, 15, champAtkSpeed);
		CallFont(hdc, 15, champRange);
		CallFont(hdc, 15, champDef);
		CallFont(hdc, 15, champHp);
		CallFont(hdc, 15, champSpeed);
		CallFont(hdc, 20, champEx);
		CallFont(hdc, 15, SkillCool);
		CallFont(hdc, 15, SpecialSkillColl);
		CallFont(hdc, 15, SkillEx);
		CallFont(hdc, 15, SpecialSkillEx);
	}
}

void ChampInformation::PrevButton()
{
	for (int i = 0; i < mChampList.size(); i++) {
		if (mChampList[i] == mCurrentChamp) {
			if (i < 1) i = mChampList.size();

			mCurrentChamp = mChampList[i - 1];
			return;
		}
	}
}

void ChampInformation::NextButton()
{
	for (int i = 0; i < mChampList.size(); i++) {
		if (mChampList[i] == mCurrentChamp) {
			if (i >= mChampList.size() - 1) i = -1;

			mCurrentChamp = mChampList[i + 1];
			return;
		}
	}
}

wstring ChampInformation::ClassTypeCheck(Champ* champ)
{
	wstring str;
	switch (champ->GetClassType())
	{
	case ClassType::Warrior:
		str = L"전사";
		break;
	case ClassType::ADCarry:
		str = L"원거리";
		break;
	case ClassType::Magician:
		str = L"마법사";
		break;
	case ClassType::Supporter:
		str = L"전투 보조";
		break;
	case ClassType::Assassin:
		str = L"암살자";
		break;
	}
	return str;
}