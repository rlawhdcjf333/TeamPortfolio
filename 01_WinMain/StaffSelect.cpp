#include "pch.h"
#include "StaffSelect.h"

StaffSelect::StaffSelect()
	:GameObject("StaffSelect")
{
	mIsActive = false;
}

void StaffSelect::Init()
{
	//Directer나 일정이나 어딘가에 있는 이번경기에 플레이어가 속한 팀의 색깔을 알아낸다, 어떻게든되것지
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
