#include "pch.h"
#include "Training.h"

Training::Training()
	:UI("Training")
{
	mIsActive = false;
}

void Training::Init()
{
	LoadFromFile("Training");

	IMAGEMANAGER->LoadFromFile(L"Training", Resources(L"Training.bmp"), 1247, 557,true);
	mImage = IMAGEMANAGER->FindImage(L"Training");

	LoadStaffList();

	if (mStaffList.size() > 0)
	{
		Staff* tmp = (Staff*)mStaffList[0];
		mCurrentStaff = tmp;

	}
}

void Training::Release()
{


}

void Training::Update()
{
	if (mIsActive)
	{
		ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("HomeToBattle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);

		string tmp = mCurrentStaff->GetStaffName();
		mCurrentStaffName.assign(tmp.begin(), tmp.end());

		mCurrentStaffAtk = mCurrentStaff->GetAtk();
		mCurrentStaffDef = mCurrentStaff->GetDef();

		for (int i = 0; i < mStaffList.size(); i++)
		{
			if (PtInRect(&mButtonList[i], _mousePosition))
			{
				Staff* tmp = (Staff*)mStaffList[i];
				mCurrentStaff = tmp;
			}

		}


		auto func = []()
		{
			ObjectManager::GetInstance()->FindObject("Training")->SetIsActive(false);
		};
		mToggleButton(5, "None", func);

	}


}

void Training::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 17, 53);
		MouseOver(hdc);

		RenderCurrentStaff(hdc);

		for (int i = 0; i < mStaffList.size(); i++)
		{
			DrawStaffList(hdc, i);
		}
	}



}

void Training:: LoadStaffList() 
{
	
	mDirector = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	auto list = mDirector->GetStaffNameList();

	for (string elem : list)
	{
		if (ObjectManager::GetInstance()->FindObject(elem) != nullptr)
		{
			mStaffList.push_back(ObjectManager::GetInstance()->FindObject(elem));
		}

	}

}

void Training::RenderCurrentStaff(HDC hdc)
{

	mCurrentStaff->UIRender(hdc, 42, 150, 55, 50);
	
	TextOut(hdc, 106, 158, mCurrentStaffName.c_str(), mCurrentStaffName.size());
	TextOut(hdc, 74, 225, to_wstring(mCurrentStaffAtk).c_str(), to_wstring(mCurrentStaffAtk).size());
	TextOut(hdc, 162, 225, to_wstring(mCurrentStaffDef).c_str(), to_wstring(mCurrentStaffDef).size());



}

void Training::DrawStaffList(HDC hdc, int i)
{
	Staff* tmp = (Staff*)mStaffList[i];
	string tmpStaffName = tmp->GetStaffName();
	wstring str;
	str.assign(tmpStaffName.begin(), tmpStaffName.end());
	DrawText(hdc, str.c_str(), str.length(), &mButtonList[i], DT_SINGLELINE | DT_VCENTER | DT_LEFT);


}

