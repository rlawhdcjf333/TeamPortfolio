#include "pch.h"
#include "StaffList.h"
#include "Training.h"
#include "StaffListDetail.h"
#include "Staff.h"
#include "Director.h"
#include "Champ.h"

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

	mIsToggleDetail = false;
	mStaffListDetail = new StaffListDetail;
	mStaffListDetail->SetStaffList(this);
	mStaffListDetail->Init();
}

void StaffList::Release()
{
	mStaffListDetail->Release();
	SafeDelete(mStaffListDetail);
}

void StaffList::Update()
{
	ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("HomeToBattle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);

	if (!mIsToggleDetail)
	{
		for (int i = 0; i < mStaffList.size(); i++)
		{
			auto func = [this, i]()
			{
				mStaffListDetail->SetStaff(mStaffList[i]);
				mStaffListDetail->SetIsActive(true);
				mIsToggleDetail = true;
			};
			mToggleButton(i, "None", func);
		}
		mToggleButton(5, "StaffList");
	}

	mStaffListDetail->Update();

}

void StaffList::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);

		for (int i = 0; i < mStaffList.size(); i++) {
			mStaffList[i]->UIRender(hdc, 53, 187 + ( i * 70), 48, 48);
			mStaffList[i]->ConditionRender(hdc, 425, 195 + ( i * 70 ), 30, 30);
			RECT charRc = RectMake(113, 212 + ( i * 70 ), 47, 25);
			RECT nameRc = RectMake(113, 187 + (i * 70), 320, 25);
			RECT atkRc = RectMake(550, 187 + (i * 70), 50, 50);
			RECT defRc = RectMake(665, 187 + (i * 70), 50, 50);
			string temp = mStaffList[i]->GetStaffName();
			wstring charStr1 = mStaffList[i]->GetCharComment(1);
			wstring nameStr = StoW(temp);
			wstring atkStr = to_wstring(mStaffList[i]->GetAtk());
			wstring defStr = to_wstring(mStaffList[i]->GetDef());
			
			HBRUSH newB = CreateSolidBrush(RGB(14, 18, 21));
			HBRUSH oldB = (HBRUSH)SelectObject(hdc, newB);
			RenderRect(hdc, charRc);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			HFONT newF = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			HFONT oldF = (HFONT)SelectObject(hdc, newF);

			DrawText(hdc, charStr1.c_str(), charStr1.length(), &charRc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			DrawText(hdc, nameStr.c_str(), nameStr.length(), &nameRc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			DrawText(hdc, atkStr.c_str(), atkStr.length(), &atkRc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			DrawText(hdc, defStr.c_str(), defStr.length(), &defRc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			SelectObject(hdc, oldF);
			DeleteObject(newF);

			auto mostList = mStaffList[i]->GetMostChamp();
			Champ* mostPick1 = (Champ*)ObjectManager::GetInstance()->FindObject(mostList.begin()->first);
			Champ* mostPick2 = (Champ*)ObjectManager::GetInstance()->FindObject(mostList.rbegin()->first);

			mostPick1->UIRender(hdc, 823, 187 + 70 * i, 48, 48);
			mostPick2->UIRender(hdc, 880, 187 + 70 * i, 48, 48);

			wstring mostPick1Pt = to_wstring(mostList.begin()->second);
			wstring mostPick2Pt = to_wstring(mostList.rbegin()->second);

			TextOut(hdc, 860, 185 + 70 * i, mostPick1Pt.c_str(), mostPick1Pt.size());
			TextOut(hdc, 916, 185 + 70 * i, mostPick2Pt.c_str(), mostPick2Pt.size());



		}

		int teamNumber = mStaffList.size();
		wstring numberStr = to_wstring(teamNumber) + L" / 5  ";
		TextOut(hdc, 140, 555, numberStr.c_str(), numberStr.size());

		mStaffListDetail->Render(hdc);
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

void StaffList::UpdateStaffList()
{
	auto list = mDirector->GetStaffNameList();
	vector<Staff*> temp;

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
