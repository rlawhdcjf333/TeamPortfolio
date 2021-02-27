#include "pch.h"
#include "GameToggle.h"
#include "ChampInfo.h"

GameToggle::GameToggle()
	:UI("GameToggle")
{
	mIsActive = false;
}

void GameToggle::Init()
{
	mButtonList.push_back({548,596,548+156,596+50});


	IMAGEMANAGER->LoadFromFile(L"GameToggle", Resources(L"GameToggle.bmp"), 162, 50, true);
	mImage = IMAGEMANAGER->FindImage(L"GameToggle");

	IMAGEMANAGER->LoadFromFile(L"GameToggleClick", Resources(L"GameToggleClick.bmp"), 162, 50, true);
	mActive = IMAGEMANAGER->FindImage(L"GameToggleClick");

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new ChampInfo);


	mChampInfo = new ChampInfo();
	mChampInfo->Init();
}

void GameToggle::Release()
{
	mChampInfo->Release();
	SafeDelete(mChampInfo);
}

void GameToggle::Update()
{
	if (mIsActive)
	{
		auto func = [this]() { mChampInfo->SetIsActive(true); };
		mToggleButton(0, "None", func);

		mChampInfo->Update();
	}

}

void GameToggle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 544, 596);
		MouseOver(hdc);
		mActive->Render(hdc, 544, 648);
		
		mChampInfo->Render(hdc);
	}

}

