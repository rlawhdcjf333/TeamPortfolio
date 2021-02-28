#include "pch.h"
#include "HelmetPepe.h"

HelmetPepe::HelmetPepe(const string& name)
	:Champ(name) 
{
	mChampName = L"HelmetPepe";
	mClassType = ClassType::Warrior;
}

void HelmetPepe::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"HelmetPepe", Resources(L"HelmetPepe.bmp"), 1040, 1440, 8, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"HelmetPepe");

	mChampEx = L"헬멧을 뒤집어 쓴 펭귄. 이유는 모르겠지만 도발적이다.";

	mFullHP = 100;
	mHP = mFullHP;
	mMP = 0;
	mAtk = 100;
	mDef = 100;
	mDistance1 = 100.f;
	mDistance2 = 100.f;
	mDistance3 = 100.f;
	mTargetDistance = 100.f;
	mAngle = 1.f;
	mRange = 100.f;
	mSpeed = 100.f;

	mAttackCool = 1.f;
	mSkill1Cool = 100.f;
	mDeathCool = 3.f;
	mSkill = 0;									//지역변수 선언 
	mSpecialSkill = 100;
}

void HelmetPepe::Release()
{
}

void HelmetPepe::Update()
{
}

void HelmetPepe::Render(HDC hdc)
{
}
