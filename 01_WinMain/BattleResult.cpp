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
	//���� 2�� �¸��� ���� �ְų� ������ ��Ⱑ 3���̸� Ȩ���� ���ư�
	
	//��Ʋ �� �ǵ������ �̵�
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
