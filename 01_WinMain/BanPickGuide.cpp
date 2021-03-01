#include "pch.h"
#include "BanPickGuide.h"
#include "ChampSelect.h"

BanPickGuide::BanPickGuide() : UI("BanPickGuide")
{
	mIsActive = false;
}

void BanPickGuide::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BanPickGuide", Resources(L"guideFrame.bmp"), 954, 480, 1, 6, true);
	mImage = IMAGEMANAGER->FindImage(L"BanPickGuide");
	mFrameY = 0;
}

void BanPickGuide::Release()
{
}

void BanPickGuide::Update()
{
	if (!mIsActive)
		return;
}

void BanPickGuide::Render(HDC hdc)
{
	if (mIsActive)
		mImage->FrameRender(hdc, 162, 80,0,mFrameY);
}

void BanPickGuide::NextFrame()
{
	if (mIsActive)
		mFrameY++;
	if (mFrameY >= 6)
	{
		ChampSelect* hptr = (ChampSelect*)ObjectManager::GetInstance()->FindObject("ChampSelect");
		hptr->SetState(SelectState::BlueBan);
		mFrameY = 0;
		mIsActive = false;
		ObjectManager::GetInstance()->FindObject("ChampSelect")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("ChampCheck")->SetIsActive(true);
	}
}