#include "pch.h"
#include "StarPixie.h"
#include "Animation.h"

StarPixie::StarPixie(const string& name)
	:Champ(name) 
{
	mChampName = L"StarPixie";
	mClassType = ClassType::Magician;
}

void StarPixie::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"StarPixie", Resources(L"StarPixie.bmp"), 900, 1440, 10, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"StarPixie");

	mChampEx = L"귀여운 스타 픽시. 마법사이자 원거리 광역 crwod cc에 특화된 챔프.";

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
	mSkillCasting = 2.5f;

	mAttackCool = 1.f;
	mSkill1Cool = 100.f;
	mDeathCool = 3.f;
	mSkill = 0;									//지역변수 선언 
	mSpecialSkill = 100;

	//애니메이션
	Animation* RightIdle = new Animation();											//오른쪽 대기모션
	RightIdle->InitFrameByStartEnd(0, 6, 5, 6, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 7, 5, 7, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* RightAttack = new Animation();
	RightAttack->InitFrameByStartEnd(0, 8, 6, 8, true);
	RightAttack->SetIsLoop(true);
	RightAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 9, 9, 9, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 10, 9, 10, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 11, 4, 11, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 5, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 1, 5, 1, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* LeftAttack = new Animation();
	LeftAttack->InitFrameByStartEnd(0, 2, 6, 2, false);
	LeftAttack->SetIsLoop(true);
	LeftAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 3, 9, 3, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 4, 9, 4, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 5, 4, 5, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));
}

void StarPixie::Release()
{
}

void StarPixie::Update()		//매지션 특성 : 스킬을 사용할 때 약간의 시전시간이 있다. (그만큼 대미지는 강함)
{
	Champ::Update();
	mSkill += Time::GetInstance()->DeltaTime();		//DeltaTime값을 받아서 대입
	

	if (mTimer >= mSkillCasting)
	{
		//공격 이미지가 앞으로 나간다.
		//공격 이미지가 Enemy에 닿아도 사라지지 않는다.
		//단 맵 밖으로 나갈경우 메모리 해제한다.
		

		mTimer = 0;
	}

	if (mMP >= mSpecialSkill)	//선언해준 마나값이 특정범위에 도달 하였을 때 궁극기 발동.
	{
		//캐스팅 시간만큼 아무런동작도 하지않고 애니메이션만 작동한다.
		//캐스팅 시간이 지났을 때 궁극기를 사용한다.
		mMP = 0;	//0으로 초기화
	}
}

void StarPixie::Render(HDC hdc)
{

}

