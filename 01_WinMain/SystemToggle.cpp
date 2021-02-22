#include "pch.h"
#include "SystemToggle.h"

SystemToggle::SystemToggle()
	:UI("SystemToggle")  
{
	mIsActive = false;
}

void SystemToggle::Init()
{
	LoadFromFile("SystemToggle");

	IMAGEMANAGER->LoadFromFile(L"SystemToggle", Resources(L"SystemToggle.bmp"), 162, 146, true);
	mImage = IMAGEMANAGER->FindImage(L"SystemToggle");

	IMAGEMANAGER->LoadFromFile(L"SystemToggleClick", Resources(L"SystemToggleClick.bmp"), 162, 50, true);
	mActive = IMAGEMANAGER->FindImage(L"SystemToggleClick");
}

void SystemToggle::Release()
{
}

void SystemToggle::Update()
{
	if (mIsActive)
	{
		auto func = []() 
		{
			ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("OnPatch")->SetIsActive(true);
		};
		mToggleButton(0, "OnPatch", func);
		mToggleButton(1, "OnPatch", func);
		mSceneChangeButton(2, L"Title", false);

	}

}

void SystemToggle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 720, 502);
		mActive->Render(hdc, 720, 648);
	}

}
