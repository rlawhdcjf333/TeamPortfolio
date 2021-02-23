#include "pch.h"
#include "StaffSelect.h"
#include "PickBattleUI.h"
StaffSelect::StaffSelect()
	: UI("StaffSelect")
{

}

void StaffSelect::Init()
{
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
	mToggleButton(1, "�����ܰ��̸����߿��ְ�", []() {mLevel = 2;});	//������ư... �ǾƷ��� �Ѱ���
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, mButtonList[0].left, mButtonList[0].top);
		//�������̶� �� �ƹ�ư �۾��� �ڸ� ���... �����ϴ� 70������
	}
}
