#include "pch.h"
#include "StaffList.h"
#include "Staff.h"

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

	LoadStaffList();
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

		for (int i = 0; i < mStaffList.size(); i++) {
			mStaffList[i]->UIRender(hdc, 53, 187 + ( i * 70), 48, 48);
		}
	}

}

void StaffList::LoadStaffList()
{

	mDirector = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	auto list = mDirector->GetStaffNameList();

	for (string elem : list)
	{
		if (ObjectManager::GetInstance()->FindObject(elem) != nullptr)
		{
			Staff* temp = (Staff*)ObjectManager::GetInstance()->FindObject(elem);
			mStaffList.push_back(temp);
		}

	}

}