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
	//���⼭ Director�� team?�� �޾Ƽ� �ش� ������ �̹����� Load/Find
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
		//�������� �̵�
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
		);	//������ư... �ڱ��ڽ��� false�� �ϰ� ������ true
	}
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{

		mImage->Render(hdc, mButtonList[50].left, mButtonList[50].top);
		//�������̶� �� �ƹ�ư �۾��� �ڸ� ���... �����ϴ� 70������
		//Staff* sst1 = ;
		/*
		wstring str =
		str.assign(BData->GetSelectStaff(0)->GetStaffName().begin(), BData->GetSelectStaff(0)->GetStaffName().end());
		TextOut(hdc, mButtonList[1].left, mButtonList[1].left, str.c_str(), str.length());
		*/
	}
}
