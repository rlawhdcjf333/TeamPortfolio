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

	LoadDirectorList(); //다시 부활 CTO
	
	mScheduleList = ScheduleManager::GetInstance()->GetSchedule();
	
	mDirector = (Director*)mDirectorList[0];
	   
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
		mImage->Render(hdc, 0, 0);

		vector<RECT> roundBox;
		vector<RECT> rectList;

		//for (int i = 0; i < mScheduleList.size(); i++) {
		//	roundBox.push_back(RectMake(36 + (i * 308), 157, 70, 15));
		//	for (int j = 0; j < mDirectorList.size() - 2; j++) {
		//		rectList.push_back(RectMake(42 + (i * 308), 186 + (j * 57), 26, 26));
		//		rectList.push_back(RectMake(68 + (i * 308), 186 + (j * 57), 215, 26));
		//		rectList.push_back(RectMake(288 + (i * 308), 186 + (j * 57), 26, 26));
		//		rectList.push_back(RectMake(42 + (i * 308), 212 + (j * 57), 26, 26));
		//		rectList.push_back(RectMake(68 + (i * 308), 212 + (j * 57), 215, 26));
		//		rectList.push_back(RectMake(288 + (i * 308), 212 + (j * 57), 26, 26));
		//	}
		//}

		for (int i = 0; i < 3; i++) {
			roundBox.push_back(RectMake(36 + (i * 308), 157, 70, 15));
			for (int j = 0; j < mDirectorList.size() / 2; j++) {
				rectList.push_back(RectMake(42 + (i * 308), 186 + (j * 57), 26, 26));
				rectList.push_back(RectMake(68 + (i * 308), 186 + (j * 57), 215, 26));
				rectList.push_back(RectMake(288 + (i * 308), 186 + (j * 57), 26, 26));
				rectList.push_back(RectMake(42 + (i * 308), 212 + (j * 57), 26, 26));
				rectList.push_back(RectMake(68 + (i * 308), 212 + (j * 57), 215, 26));
				rectList.push_back(RectMake(288 + (i * 308), 212 + (j * 57), 26, 26));
			}
		}

		MouseOver(hdc);

		RECT rc = RectMake(560, 544, 159, 28);
		wstring str1 = L"2021년 " + to_wstring(mDirector->GetMonth()) + L"월";
		HFONT newF = CreateFont(33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		HFONT oldF = (HFONT)SelectObject(hdc, newF);
		DrawText(hdc, str1.c_str(), str1.length(), &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		SelectObject(hdc, oldF);
		DeleteObject(newF);

		for (int i = 0; i <3; i++) {
			// 라운드 표시
			wstring str = to_wstring(i + 1) + L" 라운드";

			newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, str.c_str(), str.length(), &roundBox[i], DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);
		}

		for (int i = 0; i < rectList.size(); i++) {
			HBRUSH newB = CreateSolidBrush(RGB(32, 36, 39));
			HBRUSH oldB = (HBRUSH)SelectObject(hdc, newB);
			RenderRect(hdc, rectList[i]);
			SelectObject(hdc, oldB);
			DeleteObject(newB);


		}

		for (int i = 0; i < 3; i++) {
			vector<Director*>temp = mScheduleList.find(i + 1)->second;

			for (int j = 0; j < temp.size(); j++) {
				wstring str1 = L"  " + temp[j]->GetTeamName();

				//temp[j]->TeamImageRender();
				newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				oldF = (HFONT)SelectObject(hdc, newF);
				DrawText(hdc, str1.c_str(), str1.length(), &rectList[1 + (j * 3) + (i * 12)], DT_VCENTER | DT_LEFT | DT_SINGLELINE);
				SelectObject(hdc, oldF);
				DeleteObject(newF);
			}
		}


		if (mDirector->GetWeek() == 4)
		{
			Director* dir1 = mScheduleList[4][0];
			Director* dir2 = mScheduleList[4][1];

			wstring team1 = dir1->GetTeamName();
			RECT rc1 = RectMake(960, 240, 285, 70);
			wstring team2 = dir2->GetTeamName();
			RECT rc2 = RectMake(960, 360, 285, 70);

			CallFont(hdc, 50, [hdc, team1, &rc1]() {DrawText(hdc, team1.c_str(), team1.size(), &rc1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);});
			CallFont(hdc, 50, [hdc, team2, &rc2]() {DrawText(hdc, team2.c_str(), team2.size(), &rc2, DT_CENTER|DT_SINGLELINE|DT_VCENTER);});

			RECT rc3 = RectMake(1100, 335, 140, 50);
			CallFont(hdc, 30, [hdc, &rc3]() {DrawText(hdc, L"VS", 4, &rc3, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});


		}

	}
}

void Schedule::LoadDirectorList()
{
	for (int i = 1; i < 5; i++) 
	{
		mDirectorList.push_back(ObjectManager::GetInstance()->FindObject("Director" + to_string(i)));
	}
}


