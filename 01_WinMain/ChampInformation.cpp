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
	}
}

void ChampInformation::Render(HDC hdc)
{
	if (mIsActive) {
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);

		wstring ClassChampType = ClassTypeCheck(mCurrentChamp);
		wstring ChampName = mCurrentChamp->GetChampName();
		wstring ChampInformation = ChampName + L" 상세 정보";
		wstring ChampAtk = to_wstring((int)mCurrentChamp->GetAtk());
		wstring ChampAtkSpeed = to_wstring(0);
		wstring ChampRange = to_wstring(mCurrentChamp->GetRange());
		wstring ChampDef = to_wstring(mCurrentChamp->GetDef());
		wstring ChampHp = to_wstring(mCurrentChamp->GetHP());
		wstring ChampSpeed = to_wstring(mCurrentChamp->GetSpeed());

		mCurrentChamp->ChampImageRender(hdc, mRectList[1]);
		
		HFONT newF = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		HFONT oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, ChampInformation.c_str(), ChampInformation.length(), &mRectList[0], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		SelectObject(hdc, oldF);
		DeleteObject(newF);

		newF = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, ClassChampType.c_str(), ClassChampType.length(), &mRectList[2], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		SelectObject(hdc, oldF);
		DeleteObject(newF);

		newF = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, ChampName.c_str(), ChampName.length(), &mRectList[3], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		SelectObject(hdc, oldF);
		DeleteObject(newF);


		newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, ChampAtk.c_str(), ChampAtk.length(), &mRectList[4], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		DrawText(hdc, ChampAtkSpeed.c_str(), ChampAtkSpeed.length(), &mRectList[5], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		DrawText(hdc, ChampRange.c_str(), ChampRange.length(), &mRectList[6], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		DrawText(hdc, ChampDef.c_str(), ChampDef.length(), &mRectList[7], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		DrawText(hdc, ChampHp.c_str(), ChampHp.length(), &mRectList[8], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		DrawText(hdc, ChampSpeed.c_str(), ChampSpeed.length(), &mRectList[9], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		SelectObject(hdc, oldF);
		DeleteObject(newF);

		wstring ChampEx = L"챔프 설명은 랙트리스트 10번을 이용해주세요 아마 따로따로 적어서 함수로 불러내는 식으로 해야 될듯 ?? 편하대로 적어서 해주시기 바랍니다. 그럼 20000";

		newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, ChampEx.c_str(), ChampEx.length(), &mRectList[10], DT_TOP | DT_LEFT | DT_WORDBREAK);
		SelectObject(hdc, oldF);
		DeleteObject(newF);

		// 챔프 스킬 이미지를 넣고 싶으면 11 ~ 12번 랙트에다가 출력

		// 챔프 스킬 쿨타임은 13 ~ 14번 랙트

		wstring ChampSkill1 = L"챔프 스킬 설명은 15 ~ 16번을 이용해주시기 바랍니다. 아마 이것도 따로따로 해야될듯";
		wstring ChampSkill2 = L"챔프 스킬 설명은 15 ~ 16번을 이용해주시기 바랍니다. 아마 이것도 따로따로 해야될듯";

		newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, ChampSkill1.c_str(), ChampSkill1.length(), &mRectList[15], DT_TOP | DT_LEFT | DT_WORDBREAK);
		DrawText(hdc, ChampSkill2.c_str(), ChampSkill2.length(), &mRectList[16], DT_TOP | DT_LEFT | DT_WORDBREAK);
		SelectObject(hdc, oldF);
		DeleteObject(newF);
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