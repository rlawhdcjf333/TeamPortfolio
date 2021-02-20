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
		mImage->Render(hdc, 18, 503);

	}

}
