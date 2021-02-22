#include "pch.h"
#include "StaffSelect.h"
#include "PickBattleUI.h"
StaffSelect::StaffSelect()
	: GameObject("StaffSelect")
{

}

void StaffSelect::Init()
{
	//여기서 Director의 team?을 받아서 해당 색깔의 이미지를 Load/Find
	IMAGEMANAGER->LoadFromFile(L"BlueSelect", Resources(L"StaffSelect_blue.bmp"), 1080, 560, true);
	mImage = IMAGEMANAGER->FindImage(L"BlueSelect");
}

void StaffSelect::Release()
{
}

void StaffSelect::Update()
{
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, Level1Rect[70].left, Level1Rect[70].top);

	}
}

void StaffSelect::LoadFromFile(const string & fileName)
{
}

void StaffSelect::mToggleButton(int index, string UIName)
{
}
