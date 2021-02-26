#include "pch.h"
#include "ZombieMonkey.h"
#include "Animation.h"

ZombieMonkey::ZombieMonkey(const string& name)
	:Champ(name) 
{
	mChampName = L"ZombieMonkey";
	mClassType = ClassType::Supporter;
}

void ZombieMonkey::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"ZombieMonkey", Resources(L"ZombieMonkey.bmp"), 2210, 2040, 13, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"ZombieMonkey");

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

	//애니메이션
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 7, 11, 7, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 8, 5, 8, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	//힐러는 공격이 없음.
	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 9, 11, 9, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* Right_LeftSkill1ProjectBodyEffect = new Animation();
	Right_LeftSkill1ProjectBodyEffect->InitFrameByStartEnd(0, 5, 3, 5, true);
	Right_LeftSkill1ProjectBodyEffect->SetIsLoop(true);
	Right_LeftSkill1ProjectBodyEffect->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"Right_LeftSkill1ProjectBodyEffect", Right_LeftSkill1ProjectBodyEffect));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 9, 11, 9, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* Right_LeftSkill2ProjectBodyEffect = new Animation();
	Right_LeftSkill2ProjectBodyEffect->InitFrameByStartEnd(0, 6, 2, 6, true);
	Right_LeftSkill2ProjectBodyEffect->SetIsLoop(true);
	Right_LeftSkill2ProjectBodyEffect->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"Right_LeftSkill2ProjectBody", Right_LeftSkill2ProjectBodyEffect));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 11, 9, 11, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 11, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 1, 5, 1, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	//힐러는 공격이 없음.
	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 2, 11, 2, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 2, 11, 2, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 4, 9, 4, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));
}

void ZombieMonkey::Release()
{

}

void ZombieMonkey::Update()
{

}

void ZombieMonkey::Render(HDC hdc)
{

}

