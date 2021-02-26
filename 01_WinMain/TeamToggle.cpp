#include "pch.h"
#include "TeamToggle.h"
#include "StaffList.h"
#include "Training.h"
#include "NewStaff.h" 

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

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new StaffList);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Training);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new NewStaff);
}

void TeamToggle::Release()
{
}

void TeamToggle::Update()
{
	if (mIsActive) 
	{
		function <void(void)> func = [this]()
		{
			mIsActive = false;
		};
		mToggleButton(0, "StaffList", func);

		func = [this]()
		{
			mIsActive = false;
		};
		mToggleButton(1, "Training", func);

		func = [this]()
		{
			mIsActive = false;
		};
		mToggleButton(2, "NewStaff", func);
	}

}

void TeamToggle::Render(HDC hdc)
{
	
	if (mIsActive)
	{
		mImage->Render(hdc, 17, 502);
		MouseOver(hdc);
		mActive->Render(hdc, 17, 648);
	}

}
