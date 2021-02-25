#include "pch.h"
#include "Schedule.h"
#include "Director.h"

Schedule::Schedule()
	:UI("Schedule")
{
	mIsActive = false;
}

void Schedule::Init()
{
	LoadFromFile("Schedule");

	IMAGEMANAGER->LoadFromFile(L"Schedule", Resources(L"Schedule.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"Schedule");

	LoadDirectorList();
}

void Schedule::Release()
{
}

void Schedule::Update()
{
	if (mIsActive) {

		mToggleButton(3, "Schedule");
	}
}

void Schedule::Render(HDC hdc)
{
	if (mIsActive) {
		vector<RECT> rcList;
		
		mImage->Render(hdc, 0, 0);

		for (int i = 0; i < 4; i++) {
			rcList.push_back(RectMake(36 + (i * 308), 157, 70, 15));
		}

		mDirector = (Director*) mDirectorList[0];
		int week = mDirector->GetWeek() % 4;

		RECT rc = RectMake(560, 544, 159, 28);
		wstring str1 = L"2021년 " + to_wstring(mDirector->GetMonth()) + L"월";
		HFONT newF = CreateFont(33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		HFONT oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, str1.c_str(), str1.length(), &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		SelectObject(hdc, oldF);
		DeleteObject(newF);
	

		for (int i = 0; i < rcList.size(); i++) {

			wstring str = to_wstring(mDirector->GetRound()) + L" 라운드";

			newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, str.c_str(), str.length(), &rcList[i], DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);
		}
		MouseOver(hdc);
	}
}

void Schedule::LoadDirectorList()
{
	for (int i = 1; i < 5; i++) {
		mDirectorList.push_back(ObjectManager::GetInstance()->FindObject("Director" + to_string(i)));
	}
}