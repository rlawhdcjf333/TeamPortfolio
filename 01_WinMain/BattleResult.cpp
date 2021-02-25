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
	//���⼭ ���� 2�� �¸��� ���� �ְų� ������ ��Ⱑ 3���̸� Ȩ���� ���ư�
	mToggleButton(0, "BattleResult", []() {
		ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("Peedback")->SetIsActive(true);
		});
}
