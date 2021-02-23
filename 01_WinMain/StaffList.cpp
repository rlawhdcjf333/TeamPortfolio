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
			mStaffList[i]->ConditionRender(hdc, 425, 195 + ( i * 70 ), 30, 30);
			RECT charRc = RectMake(113, 212 + ( i * 70 ), 47, 25);
			RECT nameRc = RectMake(113, 187 + (i * 70), 320, 25);
			RECT atkRc = RectMake(550, 187 + (i * 70), 50, 50);
			RECT defRc = RectMake(665, 187 + (i * 70), 50, 50);
			string temp = mStaffList[i]->GetStaffName();
			wstring charStr1 = mStaffList[i]->GetCharComment(1);
			wstring nameStr;
			wstring atkStr = to_wstring(mStaffList[i]->GetAtk());
			wstring defStr = to_wstring(mStaffList[i]->GetDef());
			nameStr.assign(temp.begin(), temp.end());
			
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