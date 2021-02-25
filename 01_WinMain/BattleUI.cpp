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
			//time == 0일때 킬수를 비교해서 킬을 많이한 팀이 그 경기 승리, 대회?는 2선승하면 승리
			ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("BattleResult")->SetIsActive(true);
			return;
		}
		mDeltaTime += Time::GetInstance()->DeltaTime();//델타타임 = 1프레임이 도는 시간, 1초를 구하려면? 
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

		if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive())	//배틀중일때
		{

			TextOut(hdc, 640, 60, to_wstring(mTime).c_str(), to_wstring(mTime).size());
		}
	}
}
