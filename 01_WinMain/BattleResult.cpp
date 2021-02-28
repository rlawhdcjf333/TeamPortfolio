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
	function<void(void)> func;
	if (BData->IsEnd())
	{
		func = []() {SceneManager::GetInstance()->LoadScene(L"Home"); };
		return;
	}
	else //2승한 팀이 없으면 피드백UI활성화
	{
		func = []()
		{
			ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("Feedback")->SetIsActive(true);
		};
	}

	if (Input::GetInstance()->GetKeyDown('F'))
	{
		ObjectManager::GetInstance()->FindObject("BattleResult")->SetIsActive(false);
		func();
	}
	mToggleButton(0, "BattleResult", func);
}

void BattleResult::Render(HDC hdc)
{
	if (mIsActive)
		mImage->Render(hdc, 0, 0);
}
