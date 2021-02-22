#include "pch.h"
#include "StaffSelect.h"

StaffSelect::StaffSelect()
	:GameObject("StaffSelect")
{
	mIsActive = false;
}

void StaffSelect::Init()
{
	IMAGEMANAGER->LoadFromFile(L"LeagueToggle", Resources(L"LeagueToggle.bmp"), 162, 209, true);
	mImage = IMAGEMANAGER->FindImage(L"LeagueToggle");
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
