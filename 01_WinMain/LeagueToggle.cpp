#include "pch.h"
#include "LeagueToggle.h"
#include "Ranking.h"

LeagueToggle::LeagueToggle()
	:UI("LeagueToggle")
{
	mIsActive = false;
}

void LeagueToggle::Init()
{
	LoadFromFile("LeagueToggle");

	IMAGEMANAGER->LoadFromFile(L"LeagueToggle", Resources(L"LeagueToggle.bmp"), 162, 209, true);
	mImage = IMAGEMANAGER->FindImage(L"LeagueToggle");

	IMAGEMANAGER->LoadFromFile(L"LeagueToggleClick", Resources(L"LeagueToggleClick.bmp"), 162, 50, true);
	mActive = IMAGEMANAGER->FindImage(L"LeagueToggleClick");

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Ranking());
}

void LeagueToggle::Release()
{
}

void LeagueToggle::Update()
{
	if (mIsActive)
	{
		auto func = []()
		{
			ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
		};
		//mToggleButton(0, "", func);
		//mToggleButton(1, "", func);
		mToggleButton(2, "Ranking", func);
		//mToggleButton(3, "", func);

	}

}

void LeagueToggle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 368, 440);
		MouseOver(hdc);
		mActive->Render(hdc, 368, 648);
	}

}
