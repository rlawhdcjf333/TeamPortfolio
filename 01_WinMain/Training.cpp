#include "pch.h"
#include "Training.h"
#include "Staff.h"

Training::Training()
	:UI("Training")
{
	mIsActive = false;
}

void Training::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Training", Resources(L"Training.bmp"), 1247, 557,true);
	mImage = IMAGEMANAGER->FindImage(L"Training");

	GameObject* tmp = ObjectManager::GetInstance()->FindObject("Staff1");
	mStaffList.push_back(tmp);
	mStaffList[0]->SetIsActive(true);

}

void Training::Release()
{
}

void Training::Update()
{





}

void Training::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 17, 53);

		for (int i=0; i < mStaffList.size(); i++)
		{
			if (mStaffList[i]->GetIsActive())
			{
				Staff* tmp = (Staff*)mStaffList[i];
				tmp->UIRender(hdc, 42, 150, 55, 50);
			}
		}
	}



}
