#include "pch.h"
#include "StaffSelect.h"
#include "Staff.h"
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
	if (mIsActive)
	{
	//-

	//-
		//밴픽으로 이동
		if (Input::GetInstance()->GetKeyDown('F'))
		{
			ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(true);
			ObjectManager::GetInstance()->FindObject("BanPickGuide")->SetIsActive(true);
			ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(true);
		}
		mToggleButton(51, "StaffSelect", []() 
			{
				ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(true); 
				ObjectManager::GetInstance()->FindObject("BanPickGuide")->SetIsActive(true);
				ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(true);
			}
		);	//다음버튼... 자기자신은 false로 하고 다음걸 true
	}
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{

		mImage->Render(hdc, mButtonList[50].left, mButtonList[50].top);
		//프로필이랑 뭐 아무튼 글씨들어갈 자리 출력... 뭐로하던 70줄정도
		//Staff* sst1 = ;
		/*
		wstring str =
		str.assign(BData->GetSelectStaff(0)->GetStaffName().begin(), BData->GetSelectStaff(0)->GetStaffName().end());
		TextOut(hdc, mButtonList[1].left, mButtonList[1].left, str.c_str(), str.length());
		*/
	}
}
