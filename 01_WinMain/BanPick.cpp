#include "pch.h"
#include "BanPick.h"
#include "Child.h"
BanPick::BanPick() : UI("BanPick")
{
	mIsActive = false;
	mNowState = "BlueBan";
}

void BanPick::Init()
{
	LoadFromFile("pick_battle_level2");
	IMAGEMANAGER->LoadFromFile(L"BanPick", Resources(L"BanPick.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BanPick");
}

void BanPick::Release()
{
}

void BanPick::Update()
{
	if (!mIsActive)
		return;
	//블루 선밴 - 레드 후밴 - 블루 1픽 - 레드 1,2픽 - 블루 2,3픽 - 레드 3픽
	//1. BlueBan : ChampListUI 보여주고.. 거길누르면 그 챔프 밴되게 함, 만약 Blue 팀이 컴퓨터면 랜덤밴
	//2. RedBan : 위랑 마찬가지, 밴 된 챔프는 선택 불가
	//3. BluePick1 : 플레이 할 챔프 1명 선택	->	클릭이 일어나면... 챔프 내부의 스테프 변수 설정?
	//4. RedPick2 : 플레이 할 챔프 2명 선택
	//5. BluePick2 : 플레이 할 챔프 2명 선택
	//6. RedPick2 : 플레이 할 챔프 1명 선택
	//7. 위 과정이 끝나면 ChampCheckUI활성 + 플레이어의 팀 스태프끼리 챔피언을 바꿀 수 있는 시간이 주어지고,
	if (Input::GetInstance()->GetKeyDown(MK_LBUTTON))//테스트용임 챔프리스트 완성되면 수정
	{
		BanPickGuide* tptr = (BanPickGuide*)ObjectManager::GetInstance()->FindObject("BanPickGuide");
		tptr->NextFrame();//BanPickGuide클래스 내부 함수...에 접근하려고 ↑에서 다운캐스팅
	}
}

void BanPick::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
	}
}
