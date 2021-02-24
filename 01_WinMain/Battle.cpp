#include "pch.h"
#include "Battle.h"

Battle::Battle() : UI("Battle")
{
	mIsActive = false;
}

void Battle::Init()
{
	//누적딜힐탱량 없는 이미지도 만들어두긴함
	IMAGEMANAGER->LoadFromFile(L"BattleUI", Resources(L"battleUI.bmp"), 1280, 720, true);
	mUI = IMAGEMANAGER->FindImage(L"BattleUI");
	IMAGEMANAGER->LoadFromFile(L"BattleGround", Resources(L"battleback.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleGround");

	mTime = 60;
	mDeltaTime = 0.f;
}

void Battle::Release()
{
}

void Battle::Update()
{
	if (!mIsActive)
		return;

	if (mTime == 0 || Input::GetInstance()->GetKeyDown('G'))
	{
		mTime = 60;
		mIsActive = false;
		//종료를 표시할 UI를 띄우고 싶으면 그 UI내에서 Battle과 peedback active를 세팅
		ObjectManager::GetInstance()->FindObject("Peedback")->SetIsActive(true);		//Peedback 정리되면 주석 제거
	}
	mDeltaTime += Time::GetInstance()->DeltaTime();	//일단해봄, 초 측정할려고.. DeltaTime이 0.n인 실수인가?
	if (mDeltaTime >= 1)
	{
		mDeltaTime = 0.f;
		mTime -= 1;//델타타임 = 1프레임이 도는 시간, 1초를 구하려면? 
	}
}

void Battle::Render(HDC hdc)
{
	//1. 배경
	mImage->Render(hdc, 0, 0);
	//2. UI : 상단부분 + 좌우 정보 + 킬데스 로그 및 리스폰시간
	mUI->Render(hdc, 0, 0);
	TextOut(hdc, 640, 60, to_wstring(mTime).c_str(), to_wstring(mTime).size());
	//3. 챔프
}
