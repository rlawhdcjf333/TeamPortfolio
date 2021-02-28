#include "pch.h"
#include "ChampSelect.h"
#include "Champ.h"

ChampSelect::ChampSelect()
	:UI("ChampSelect")
{
	mIsActive = false;
}

void ChampSelect::Init()
{
	LoadFromFile("ChampSelect");

	mChampList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Champ);

	mCurrentChamp = nullptr;

}

void ChampSelect::Release()
{
}

void ChampSelect::Update()
{



}

void ChampSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		for (int i = 0; i < mChampList.size(); i++)
		{
			ChampRender(hdc, 232+i*80, 182, mChampList, i);
		}
		
		MouseOver(hdc);
	}
}

void ChampSelect::ChampRender(HDC hdc, int x , int y, vector<GameObject*> list, int i)
{

	RECT outBox = RectMake(x, y, 77, 103);
	CallBrush(hdc, RGB(16, 18, 22), [hdc, outBox]() {RenderRect(hdc, outBox);});

	RECT inBox = RectMake(x + 2, y + 2, 72, 72);
	CallBrush(hdc, RGB(55, 57, 61), [hdc, inBox]() {RenderRect(hdc, inBox);});

	Champ* champ = (Champ*)list[i];
	champ->UIRender(hdc, x+2, y+2, 70, 70);

	wstring champName = champ->GetChampName();
	RECT nameBox = RectMake(x, y + 74, 77, 30);
	CallFont(hdc, 12, [hdc, champName, &nameBox]() {DrawText(hdc, champName.c_str(), champName.size(), &nameBox, DT_SINGLELINE | DT_VCENTER | DT_CENTER);});



}
