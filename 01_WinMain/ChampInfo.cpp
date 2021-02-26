#include "pch.h"
#include "ChampInfo.h"
#include "Champ.h"

ChampInfo::ChampInfo()
	:UI("ChampInfo")
{
	mIsActive = false;
}

void ChampInfo::Init()
{
	LoadFromFile("ChampInfo");

	IMAGEMANAGER->LoadFromFile(L"ChampInfo", Resources(L"ChampInfo.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"ChampInfo");

	LoadAllChampList();
}

void ChampInfo::Release()
{
}

void ChampInfo::Update()
{
	if (mIsActive)
	{

		mToggleButton(6, "ChampInfo");
	}

}

void ChampInfo::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);

		vector<RECT> rectList;
		for (int i = 0; i < mChampList.size(); i++) {
			rectList.push_back(RectMake(44 + (i * 120), 150, 110, 25));
			rectList.push_back(RectMake(44 + (i * 120), 175, 110, 115));
			rectList.push_back(RectMake(44 + (i * 120), 290, 110, 35));
		}

		for (int i = 0; i < mChampList.size(); i++) {


			HBRUSH newB = CreateSolidBrush(RGB(53, 58, 61));
			HBRUSH oldB = (HBRUSH)SelectObject(hdc, newB);
			RenderRect(hdc, rectList[1 + (i * 3)]);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			newB = CreateSolidBrush(RGB(17, 19, 23));
			oldB = (HBRUSH)SelectObject(hdc, newB);
			RenderRect(hdc, rectList[0 + (i * 3)]);
			RenderRect(hdc, rectList[2 + (i * 3)]);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			mChampList[i]->Render(hdc);

			ClassTypeCheck();

			string temp = mChampList[i]->GetName();
			wstring champClass = L"  " + mClassTypeName;
			wstring champName;
			champName.assign(temp.begin(), temp.end());

			HFONT newF = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			HFONT oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, champName.c_str(), champName.length(), &rectList[2 + (i * 3)], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);

			newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, champClass.c_str(), champClass.length(), &rectList[0 + (i * 3)], DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);
		}
	}

}

void ChampInfo::LoadAllChampList()
{
	for (int i = 1; i < 3; i++) {
		mChampList.push_back((Champ*)ObjectManager::GetInstance()->FindObject("Champ" + to_string(i)));
	}
}

void ChampInfo::LoadWarriorChampList()
{

}

void ChampInfo::LoadADCarryChampList()
{
}

void ChampInfo::LoadMagicanChampList()
{
}

void ChampInfo::LoadSupoterChampList()
{
}

void ChampInfo::LoadAssassinChampList()
{
}

void ChampInfo::ClassTypeCheck()
{
	for (int i = 0; i < mChampList.size(); i++) {
		switch (mChampList[i]->GetClassType())
		{
		case ClassType::Warrior:
			mClassTypeName = L"전사";
			break;
		case ClassType::ADCarry:
			mClassTypeName = L"원거리";
			break;
		case ClassType::Magician:
			mClassTypeName = L"마법사";
			break;
		case ClassType::Supoter:
			mClassTypeName = L"전투 보조";
			break;
		case ClassType::Assassin:
			mClassTypeName = L"암살자";
			break;
		}
	}
}
