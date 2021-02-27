#include "pch.h"
#include "Sponsor.h"

Sponsor::Sponsor()
	:UI("Sponsor")
{
	mIsActive = false;
}

void Sponsor::Init()
{
	LoadFromFile("Sponsor");
	IMAGEMANAGER->LoadFromFile(L"Sponsor", Resources(L"Sponsor.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"Sponsor");
}

void Sponsor::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);
	}
}

void Sponsor::Release()
{
}

void Sponsor::Update()
{
	ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("HomeToBattle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);


	mToggleButton(10, "Sponsor");

}
