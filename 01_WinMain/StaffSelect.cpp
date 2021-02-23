#include "pch.h"
#include "StaffSelect.h"
#include "PickBattleUI.h"
StaffSelect::StaffSelect()
	: UI("StaffSelect")
{

}

void StaffSelect::Init()
{
	//여기서 Director의 team?을 받아서 해당 색깔의 이미지를 Load/Find
	IMAGEMANAGER->LoadFromFile(L"BlueSelect", Resources(L"StaffSelect_blue.bmp"), 1080, 560, true);
	IMAGEMANAGER->LoadFromFile(L"RedSelect", Resources(L"StaffSelect_red.bmp"), 1080, 560, true);
	mImage = IMAGEMANAGER->FindImage(L"BlueSelect");
}

void StaffSelect::Release()
{
}

void StaffSelect::Update()
{
	//-
	//-
	mToggleButton(1, "다음단계이름나중에넣고", []() {mLevel = 2;});	//다음버튼... 맨아래에 둘거임
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, mButtonList[0].left, mButtonList[0].top);
		//프로필이랑 뭐 아무튼 글씨들어갈 자리 출력... 뭐로하던 70줄정도
	}
}
