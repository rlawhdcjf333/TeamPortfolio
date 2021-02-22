#include "pch.h"
#include "TeamToggle.h"
#include "Training.h"
#include "Staff.h"

TeamToggle::TeamToggle()
	:UI("TeamToggle") 
{
	mIsActive = false;
}

void TeamToggle::Init()
{
	LoadFromFile("TeamToggle");

	IMAGEMANAGER->LoadFromFile(L"TeamToggle", Resources(L"TeamToggle.bmp"), 162, 146, true);
	mImage=IMAGEMANAGER->FindImage(L"TeamToggle");

	IMAGEMANAGER->LoadFromFile(L"TeamToggleClick", Resources(L"TeamToggleClick.bmp"), 162, 50, true);
	mActive= IMAGEMANAGER->FindImage(L"TeamToggleClick");

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Training);

}

void TeamToggle::Release()
{
}

void TeamToggle::Update()
{
	if (mIsActive) 
	{
		auto func = []()
		{
			ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);
		};
		mToggleButton(1, "Training", func);

	}

}

void TeamToggle::Render(HDC hdc)
{
	
	if (mIsActive)
	{
		mImage->Render(hdc, 17, 502);
		mActive->Render(hdc, 17, 648);
	}

}
