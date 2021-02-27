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

	mRectList.push_back(RectMake(50, 242, 190, 200));
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

		mCurrentChamp->ChampImageRender(hdc, mRectList[0]);
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
