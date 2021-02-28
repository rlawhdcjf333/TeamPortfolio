#include "pch.h"
#include "MistKnight.h"
#include "Animation.h"

MistKnight::MistKnight(const string& name)
	:Champ(name) 
{
	mChampName = L"MistKnight";
	mClassType = ClassType::Assassin;
}

void MistKnight::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"MistKnight", Resources(L"MistKnight.bmp"), 1680, 1680, 12, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"MistKnight");

	mChampEx = L"검은 천을 뒤집어 쓴 암살귀. 그의 눈을 본 사람은 보통 오래 살지 못한다고 한다.";
	
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
	RightIdle->InitFrameByStartEnd(0, 1, 5, 1, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 3, 5, 3, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* RightAttack = new Animation();								//여기 주시
	RightAttack->InitFrameByStartEnd(0, 5, 5, 5, true);
	RightAttack->SetIsLoop(true);
	RightAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 7, 11, 7, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 7, 11, 7, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));
	
	Animation* RightSkill2HitEffect = new Animation();
	RightSkill2HitEffect->InitFrameByStartEnd(0, 9, 1, 9, true);
	RightSkill2HitEffect->SetIsLoop(true);
	RightSkill2HitEffect->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2HitEffect", RightSkill2HitEffect));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 11, 6, 11, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 5, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 2, 5, 2, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* LeftAttack = new Animation();								//여기 주시
	LeftAttack->InitFrameByStartEnd(0, 4, 5, 4, false);
	LeftAttack->SetIsLoop(true);
	LeftAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 6, 11, 6, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 6, 11, 6, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));
	
	Animation* LeftSkill2HitEffect = new Animation();
	LeftSkill2HitEffect->InitFrameByStartEnd(0, 8, 1, 8, false);
	LeftSkill2HitEffect->SetIsLoop(true);
	LeftSkill2HitEffect->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2HitEffect", LeftSkill2HitEffect));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 10, 6, 10, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));
}

void MistKnight::Release()
{

}

void MistKnight::Update()
{

}

void MistKnight::Render(HDC hdc)
{

}


