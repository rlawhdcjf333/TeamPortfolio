#include "pch.h"
#include "BanPick.h"
#include "Child.h"
BanPick::BanPick() : UI("BanPick")
{
	mIsActive = false;
}

void BanPick::Init()
{
	LoadFromFile("pick_battle_level2");
	IMAGEMANAGER->LoadFromFile(L"BanPick", Resources(L"banpick.bmp"), 1280, 720, true);
	IMAGEMANAGER->LoadFromFile(L"None", Resources(L"null.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BanPick");
	mNowState = "BlueBan";
}

void BanPick::Release()
{
}

void BanPick::Update()
{
	if (!mIsActive)
		return;

	if (!ObjectManager::GetInstance()->FindObject("BanPickGuide")->GetIsActive())
		mImage = IMAGEMANAGER->FindImage(L"None");
	else
		mImage = IMAGEMANAGER->FindImage(L"BanPick");
}

void BanPick::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
	}
}
