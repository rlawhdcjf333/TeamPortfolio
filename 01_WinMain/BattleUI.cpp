#include "pch.h"
#include "BattleUI.h"

BattleUI::BattleUI() : UI("BattleUI")
{
	mIsActive = false;
}

void BattleUI::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BattleUI", Resources(L"battleUI.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleUI");
	
	mTime = 60;
	mDeltaTime = 0.f;
}

void BattleUI::Release()
{
}

void BattleUI::Update()
{
	if (!mIsActive)
	{
		return;
	}


	if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive())
	{
		if (mTime == 0 || Input::GetInstance()->GetKeyDown('G'))
		{
			//time == 0�϶� ų���� ���ؼ� ų�� ������ ���� �� ��� �¸�, ��ȸ?�� 2�����ϸ� �¸�
			ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("BattleResult")->SetIsActive(true);
			return;
		}
		mDeltaTime += Time::GetInstance()->DeltaTime();//��ŸŸ�� = 1�������� ���� �ð�, 1�ʸ� ���Ϸ���? 
		if (mDeltaTime >= 1)
		{
			mDeltaTime = 0.f;
			mTime -= 1;
		}
	}
	else
	{
		mTime = 60;
	}
}

void BattleUI::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);

		if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive())	//��Ʋ���϶�
		{

			TextOut(hdc, 640, 60, to_wstring(mTime).c_str(), to_wstring(mTime).size());
		}
	}
}
