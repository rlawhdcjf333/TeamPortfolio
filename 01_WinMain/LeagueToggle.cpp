#include "pch.h"
#include "LeagueToggle.h"
#include "Ranking.h"
#include "Schedule.h"

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
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Schedule());
}

void LeagueToggle::Release()
{
}

void LeagueToggle::Update()
{
	if (mIsActive)
	{
		auto func = [this]() //this 캡쳐 적극 활용 바람 - CTO
		{
			mIsActive = false;
		};
		mToggleButton(0, "OnPatch", func); //OnPatch를 넣으면 준비중 멘트가 출력된다
		mToggleButton(1, "OnPatch", func);
		mToggleButton(2, "Ranking", func);
		mToggleButton(3, "Schedule", func);

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
