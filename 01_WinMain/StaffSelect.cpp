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
	//-

	//-
	if (mIsActive)
	{
		mToggleButton(51, "StaffSelect", []() 
			{ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(false); });	//������ư... �ڱ��ڽ��� false�� �ϰ� ������ true
	}
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, mButtonList[50].left, mButtonList[50].top);
		//�������̶� �� �ƹ�ư �۾��� �ڸ� ���... �����ϴ� 70������
	}
}
