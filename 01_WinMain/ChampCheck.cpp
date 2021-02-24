#include "pch.h"
#include "ChampCheck.h"

ChampCheck::ChampCheck() : UI("ChampCheck")
{
	mIsActive = false;
}

void ChampCheck::Init()
{
	LoadFromFile("ChampCheck");
	IMAGEMANAGER->LoadFromFile(L"ChampCheck", Resources(L"ChampCheck.bmp"), 364, 302, true);
	mImage = IMAGEMANAGER->FindImage(L"ChampCheck");
}

void ChampCheck::Release()
{
}

void ChampCheck::Update()
{
	if (!mIsActive)
		return;

	if (Input::GetInstance()->GetKeyDown('F'))
	{
		ObjectManager::GetInstance()->FindObject("ChampCheck")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(false);
		//ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(true);
	}
	mToggleButton(1, "ChampCheck", []() {
		ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(false); 
		//ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(true);	//배틀 작업하면 주석 제거
	});
}

void ChampCheck::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, mButtonList[0].left, mButtonList[0].top);
	}
}
