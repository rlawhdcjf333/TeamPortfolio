#include "pch.h"
#include "StaffSelect.h"
StaffSelect::StaffSelect()
	: UI("StaffSelect")
{
	mIsActive = false;
}

void StaffSelect::Init()
{
	LoadFromFile("staffSelect");
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
	if (mIsActive)
	{
		mToggleButton(51, "StaffSelect", []() 
			{ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(false); });	//다음버튼... 자기자신은 false로 하고 다음걸 true
	}
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, mButtonList[50].left, mButtonList[50].top);
		//프로필이랑 뭐 아무튼 글씨들어갈 자리 출력... 뭐로하던 70줄정도
	}
}
