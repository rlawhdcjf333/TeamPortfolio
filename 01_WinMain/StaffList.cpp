#include "pch.h"
#include "StaffList.h"

StaffList::StaffList()
	:UI("StaffList")
{
	mIsActive = false;
}

void StaffList::Init()
{
	LoadFromFile("StaffList");

	IMAGEMANAGER->LoadFromFile(L"StaffList", Resources(L"StaffList.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"StaffList");

}

void StaffList::Release()
{
}

void StaffList::Update()
{
	if (mIsActive)
	{

		mToggleButton(5, "StaffList");
	}



}

void StaffList::Render(HDC hdc)
{
	if (mIsActive)
	{






		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);
	}

}


