#include "pch.h"
#include "StaffSelect.h"

StaffSelect::StaffSelect()
	:GameObject("StaffSelect")
{
	mIsActive = false;
}

void StaffSelect::Init()
{
	//Directer�� �����̳� ��򰡿� �ִ� �̹���⿡ �÷��̾ ���� ���� ������ �˾Ƴ���, ��Ե�ǰ���
	IMAGEMANAGER->LoadFromFile(L"StaffSelectBlue", Resources(L"StaffSelect_blue.bmp"), 1080, 560, true);
	mImage = IMAGEMANAGER->FindImage(L"StaffSelect_blue");
}

void StaffSelect::Release()
{
}

void StaffSelect::Update()
{
}

void StaffSelect::Render(HDC hdc)
{
}
