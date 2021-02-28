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
	//배틀 씬 종료 트리거
	function<void(void)> func;
	if (BData->IsEnd())
	{
		func = []() {SceneManager::GetInstance()->LoadScene(L"Home"); };
		return;
	}
	else //배틀 씬 반복 트리거
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
