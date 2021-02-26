#include "pch.h"
#include "ChampInfo.h"
#include "ChampManager.h"
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
			rectList.push_back(RectMake(49 + (i * 125), 155, 110, 25));
			rectList.push_back(RectMake(49 + (i * 125), 180, 110, 115));
			rectList.push_back(RectMake(49 + (i * 125), 295, 110, 35));
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

			Champ* champ = (Champ*)mChampList[i];
			champ->ChampImageRender(hdc, rectList[1 + (i * 3)]);

			ClassTypeCheck(i);

			wstring temp = champ->GetChampName();
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
	mChampList = ChampManager::GetInstance()->GetChampList();
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

void ChampInfo::ClassTypeCheck(int index)
{
	Champ* champ = (Champ*)mChampList[index];
	switch (champ->GetClassType())
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
	case ClassType::Supporter:
		mClassTypeName = L"전투 보조";
		break;
	case ClassType::Assassin:
		mClassTypeName = L"암살자";
		break;
	}
	
}
