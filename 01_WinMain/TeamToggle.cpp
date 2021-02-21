#include "pch.h"
#include "TeamToggle.h"

TeamToggle::TeamToggle()
	:GameObject("TeamToggle")
{
	mIsActive = false;
}

void TeamToggle::Init()
{
	IMAGEMANAGER->LoadFromFile(L"TeamToggle", Resources(L"TeamToggle.bmp"), 162, 146, true);
	mImage=IMAGEMANAGER->FindImage(L"TeamToggle");

	IMAGEMANAGER->LoadFromFile(L"TeamToggleClick", Resources(L"TeamToggleClick.bmp"), 162, 50, true);
	mActive= IMAGEMANAGER->FindImage(L"TeamToggleClick");
}

void TeamToggle::Release()
{
}

void TeamToggle::Update()
{
	if (mIsActive) 
	{



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
