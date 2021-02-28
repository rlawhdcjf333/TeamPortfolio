#include "pch.h"
#include "Battle.h"

Battle::Battle() : UI("Battle")
{
	mIsActive = false;
}

void Battle::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BattleGround", Resources(L"battleback.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleGround");
}

void Battle::Release()
{
}

void Battle::Update()
{
	


	






}

void Battle::Render(HDC hdc)
{
	//1. 배경
	mImage->Render(hdc, 0, 0);
	//2. UI : 상단부분 + 좌우 정보 + 킬데스 -> BattleUI에서 표시
	//3. 챔프
}
