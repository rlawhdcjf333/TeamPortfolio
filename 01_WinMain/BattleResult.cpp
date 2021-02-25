#include "pch.h"
#include "BattleResult.h"

BattleResult::BattleResult() : UI("BattleResult")
{
	mIsActive = false;
}

void BattleResult::Init()
{
	LoadFromFile("BattleResult");
	IMAGEMANAGER->LoadFromFile(L"BattleResult", Resources(L"BattleResult.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleResult");
}

void BattleResult::Update()
{
	if (!mIsActive)
		return;
	//만약 2번 승리한 팀이 있거나 진행한 경기가 3판이면 홈으로 돌아감
	
	//배틀 후 피드백으로 이동
	if (Input::GetInstance()->GetKeyDown('F'))
	{
		ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("Peedback")->SetIsActive(true);
		ObjectManager::GetInstance()->FindObject("BattleResult")->SetIsActive(false);
	}
	mToggleButton(0, "BattleResult", []() {
		ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("Peedback")->SetIsActive(true);
		});
}

void BattleResult::Render(HDC hdc)
{
	if (mIsActive)
		mImage->Render(hdc, 0, 0);
}
