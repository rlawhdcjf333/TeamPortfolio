#include "pch.h"
#include "LeagueToggle.h"

LeagueToggle::LeagueToggle()
	:GameObject("LeagueToggle")
{
	mIsActive = false;
}

void LeagueToggle::Init()
{
	IMAGEMANAGER->LoadFromFile(L"LeagueToggle", Resources(L"LeagueToggle.bmp"), 162, 209, true);
	mImage = IMAGEMANAGER->FindImage(L"LeagueToggle");

	IMAGEMANAGER->LoadFromFile(L"LeagueToggleClick", Resources(L"LeagueToggleClick.bmp"), 162, 50, true);
	mActive = IMAGEMANAGER->FindImage(L"LeagueToggleClick");
}

void LeagueToggle::Release()
{
}

void LeagueToggle::Update()
{
	if (mIsActive)
	{



	}

}

void LeagueToggle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 368, 440);
		mActive->Render(hdc, 368, 648);
	}

}
