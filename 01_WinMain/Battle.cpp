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
	//1. ���
	mImage->Render(hdc, 0, 0);
	//2. UI : ��ܺκ� + �¿� ���� + ų���� -> BattleUI���� ǥ��
	//3. è��
}
