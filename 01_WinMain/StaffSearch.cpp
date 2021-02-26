#include "pch.h"
#include "StaffSearch.h"
#include "StaffResult.h"
#include "Director.h"

StaffSearch::StaffSearch(int x, int y, Director* dir)
	:UI("StaffSearch")
{
	mIsActive = false;
	mX = x;
	mY = y;
	mDirector = dir;
}

void StaffSearch::Init()
{
	IMAGEMANAGER->LoadFromFile(L"StaffSearch", Resources(L"StaffSearch.bmp"), 294, 384, true);
	mImage = IMAGEMANAGER->FindImage(L"StaffSearch");

	RECT rc = RectMake(mX + 83, mY + 337, 128, 30);
	mButtonList.push_back(rc);

	mStaffResult = new StaffResult(mX, mY, mDirector);

}

void StaffSearch::Release()
{
	mStaffResult->Release();
	SafeDelete(mStaffResult);
}

void StaffSearch::Update()
{
	mStaffResult->Update();

	auto func = [this]()
	{
		if (mDirector->GetGold() >= 10)
		{
			mStaffResult->Init();
			mDirector->SetGold(mDirector->GetGold() - 10);
			mStaffResult->SetIsActive(true);
		}
	};
	mToggleButton(0, "None", func);


}

void StaffSearch::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, mX, mY);
		MouseOver(hdc);

		mStaffResult->Render(hdc);
	}
}
