#include "pch.h"
#include "NewStaff.h"
#include "Director.h"
#include "StaffSearch.h"

NewStaff::NewStaff()
	:UI("NewStaff")
{
	mIsActive = false;
}

void NewStaff::Init()
{
	LoadFromFile("NewStaff");

	IMAGEMANAGER->LoadFromFile(L"NewStaff", Resources(L"NewStaff.bmp"), 1280, 719, true);
	mImage = IMAGEMANAGER->FindImage(L"NewStaff");

	mDirector = (Director*)ObjectManager::GetInstance()->FindObject("Director1");

	mStaffSearchList.push_back(new StaffSearch(35, 135, mDirector));
	mStaffSearchList.push_back(new StaffSearch(340, 135, mDirector));
	mStaffSearchList.push_back(new StaffSearch(646, 135, mDirector));
	mStaffSearchList.push_back(new StaffSearch(950, 135, mDirector));
	
	for (StaffSearch*& elem : mStaffSearchList)
	{
		elem->Init();
		elem->SetIsActive(true);
	}

}

void NewStaff::Release()
{
	for (StaffSearch*& elem : mStaffSearchList)
	{
		elem->Release();
		SafeDelete(elem);
	}
}

void NewStaff::Update()
{
	if (mIsActive)
	{
		ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("HomeToBattle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);

		mToggleButton(0, "NewStaff");

		for (StaffSearch*& elem : mStaffSearchList)
		{
			elem->Update();
		}


	}
}

void NewStaff::Render(HDC hdc)
{
	if (mIsActive)
	{

		mImage->Render(hdc, 0, 0);

		//현재 소지금 표시
		int gold = mDirector->GetGold();
		wstring goldstr = to_wstring(gold);
		RECT goldRect = RectMake(180, 550, 60, 30);
		DrawText(hdc, goldstr.c_str(), goldstr.size(), &goldRect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

		MouseOver(hdc);

		for (StaffSearch* elem : mStaffSearchList)
		{
			elem->Render(hdc);
		}

	}

}
