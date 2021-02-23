#include "pch.h"
#include "ChampInfo.h"

ChampInfo::ChampInfo()
	:UI("ChampInfo")
{
	mIsActive = false;
}

void ChampInfo::Init()
{
	LoadFromFile("ChampInfo");

	IMAGEMANAGER->LoadFromFile(L"ChampInfo", Resources(L"ChampInfo.bmp"), 1247, 552, true);
	mImage = IMAGEMANAGER->FindImage(L"ChampInfo");
	
}

void ChampInfo::Release()
{
}

void ChampInfo::Update()
{
	if (mIsActive)
	{

		mToggleButton(6, "ChampInfo");
	}

}

void ChampInfo::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 18,55);
		MouseOver(hdc);
	}

}


