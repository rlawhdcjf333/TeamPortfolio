#include "pch.h"
#include "BattleResult.h"

BattleResult::BattleResult() : UI("BattleResult")
{
	mIsActive = false;
}

void BattleResult::Init()
{
	LoadFromFile("BattleResult");
}

void BattleResult::Update()
{
	if (!mIsActive)
		return;
	//여기서 만약 2번 승리한 팀이 있거나 진행한 경기가 3판이면 홈으로 돌아감
	mToggleButton(0, "BattleResult", []() {
		ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("Peedback")->SetIsActive(true);
		});
}
