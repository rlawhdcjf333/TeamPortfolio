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

	mRectList.push_back(RectMakeCenter(WINSIZEX / 2, 92, 412, 42)); // ~ è�� �� ����
	mRectList.push_back(RectMake(50, 242, 190, 200));	// è�� �̹���
	mRectList.push_back(RectMakeCenter(145, 217, 120, 26));	// è�� Ÿ��
	mRectList.push_back(RectMake(47, 456, 195, 58));	// è�� �̸�

	for (int i = 0; i < 6; i++) {	// è�� �ɷ�ġ
		mRectList.push_back(RectMake(390, 212 + (i * 26), 46, 26));
	}

	mRectList.push_back(RectMake(456, 212, 370, 154));	// è�� ����
	
	for (int i = 0; i < 2; i++) {	// è�� ��ų ������ �̹���
		mRectList.push_back(RectMake(284, 390 + (i * 70), 48, 48));
	}

	for (int i = 0; i < 2; i++) {	// è�� ��ų ��
		mRectList.push_back(RectMake(360, 417 + (i * 70), 74, 20));
	}

	for (int i = 0; i < 2; i++) {	// è�� ��ų ����
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
		wstring ChampInformation = ChampName + L" �� ����";
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

		wstring ChampEx = L"è�� ������ ��Ʈ����Ʈ 10���� �̿����ּ��� �Ƹ� ���ε��� ��� �Լ��� �ҷ����� ������ �ؾ� �ɵ� ?? ���ϴ�� ��� ���ֽñ� �ٶ��ϴ�. �׷� 20000";

		newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, ChampEx.c_str(), ChampEx.length(), &mRectList[10], DT_TOP | DT_LEFT | DT_WORDBREAK);
		SelectObject(hdc, oldF);
		DeleteObject(newF);

		// è�� ��ų �̹����� �ְ� ������ 11 ~ 12�� ��Ʈ���ٰ� ���

		// è�� ��ų ��Ÿ���� 13 ~ 14�� ��Ʈ

		wstring ChampSkill1 = L"è�� ��ų ������ 15 ~ 16���� �̿����ֽñ� �ٶ��ϴ�. �Ƹ� �̰͵� ���ε��� �ؾߵɵ�";
		wstring ChampSkill2 = L"è�� ��ų ������ 15 ~ 16���� �̿����ֽñ� �ٶ��ϴ�. �Ƹ� �̰͵� ���ε��� �ؾߵɵ�";

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
		str = L"����";
		break;
	case ClassType::ADCarry:
		str = L"���Ÿ�";
		break;
	case ClassType::Magician:
		str = L"������";
		break;
	case ClassType::Supporter:
		str = L"���� ����";
		break;
	case ClassType::Assassin:
		str = L"�ϻ���";
		break;
	}
	return str;
}