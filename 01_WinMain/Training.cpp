#include "pch.h"
#include "Training.h"
#include "Staff.h"
#include "Director.h"
#include "TrainingDetail.h"
#include "Champ.h"

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

	mTrainingDetail = new TrainingDetail;
	mTrainingDetail->Init(); //얘는 매니저에 등록 안함 init 필수

	LoadStaffList();

	if (mStaffList.size() > 0)
	{
		Staff* tmp = (Staff*)mStaffList[0];
		mCurrentStaff = tmp;
	}
}

void Training::Release()
{
	SafeDelete(mTrainingDetail);
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
		mCurrentStaffTrainingPoint = mCurrentStaff->GetTrainingPoint();

		for (int i = 0; i < mStaffList.size(); i++)
		{
			if (PtInRect(&mButtonList[i], _mousePosition))
			{
				Staff* tmp = (Staff*)mStaffList[i];
				mCurrentStaff = tmp;

				if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
				{
					mSelectedStaff = mCurrentStaff;
					mTrainingDetail->SetStaff(mSelectedStaff);
					mSelection = mButtonList[i];
					mTrainingDetail->SetIsActive(true);
				}
			}
		}

		mTrainingDetail->Update();

		auto func = [this]()
		{
			mIsActive = false;
			mTrainingDetail->SetIsActive(false);
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

		HBRUSH newB = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldB = (HBRUSH)SelectObject(hdc, newB);
		HPEN newP = CreatePen(PS_SOLID, 5, RGB(95, 223, 0));
		HPEN oldP = (HPEN)SelectObject(hdc, newP);
		RenderRect(hdc, mSelection);
		SelectObject(hdc, oldB);
		DeleteObject(newB);
		SelectObject(hdc, oldP);
		DeleteObject(newP);

		mTrainingDetail->Render(hdc);


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

	RECT CharRc = RectMake(108, 182, 47, 21);
	DrawText(hdc, mCurrentStaff->GetCharComment(1).c_str(), mCurrentStaff->GetCharComment(1).size(), &CharRc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	auto list = mCurrentStaff->GetMostChamp();
	Champ* most1 = (Champ*)ObjectManager::GetInstance()->FindObject(list.begin()->first);
	Champ* most2 = (Champ*)ObjectManager::GetInstance()->FindObject(list.rbegin()->first);

	most1->UIRender(hdc, 356, 205, 48, 48);
	most2->UIRender(hdc, 414, 205, 48, 48);

}

void Training::DrawStaffList(HDC hdc, int i)
{
	Staff* tmp = (Staff*)mStaffList[i];

	string tmpStaffName = tmp->GetStaffName();
	wstring str;
	str.assign(tmpStaffName.begin(), tmpStaffName.end());
	DrawText(hdc, str.c_str(), str.length(), &mButtonList[i], DT_SINGLELINE | DT_VCENTER | DT_LEFT);

	int tmpStaffTrainingPoint = tmp->GetTrainingPoint();
	wstring pt = to_wstring(tmpStaffTrainingPoint) + L"         ";
	DrawText(hdc, pt.c_str(), pt.length(), &mButtonList[i], DT_SINGLELINE | DT_VCENTER | DT_RIGHT);


}

void Training::UpdateStaffList()
{
	auto list = mDirector->GetStaffNameList();
	vector <Staff*> temp;

	for (string elem : list)
	{
		if (ObjectManager::GetInstance()->FindObject(elem) != nullptr)
		{
			Staff* tmp = (Staff*)ObjectManager::GetInstance()->FindObject(elem);
			temp.push_back(tmp);
		}

	}

	mStaffList.assign(temp.begin(), temp.end());

}

