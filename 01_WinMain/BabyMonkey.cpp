#include "pch.h"
#include "BabyMonkey.h"
#include "Animation.h"

BabyMonkey::BabyMonkey(const string& name )
	:Champ(name) 
{
	mChampName = L"BabyMonkey";
	mClassType = ClassType::Supporter;
}

void BabyMonkey::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"BabyMonkey", Resources(L"BabyMonkey.bmp"), 480, 600, 6, 10, true);
	mImage = IMAGEMANAGER->FindImage(L"BabyMonkey");

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"MonkeySkill", Resources(L"SkillIcon/MonkeySkill.bmp"), 62, 62, true);
	mSkillImage = IMAGEMANAGER->FindImage(L"MonkeySkill");

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"MonkeySpecialSkill", Resources(L"SkillIcon/MonkeySpecialSkill.bmp"), 62, 62, true);
	mSpecialSkillImage = IMAGEMANAGER->FindImage(L"MonkeySpecialSkill");

	mChampEx = L"ť��Ʈ�� �ǰ� ���� �Ʊ� ������. �Ʊ��� ġ���ϴµ� �����̴�.";
	mSkillEx = L"����� ������ �ֺ� ���� ������ �Ʊ��� ȸ����Ų��.";
	mSpecialSkillEx = L"������ ����� ������ �ֺ� ���� ������ �Ʊ��� 3�� ȸ����Ų��.";
	
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
	mSkill = 0;									//�������� ���� 
	mSpecialSkill = 100;

	//�ִϸ��̼�
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 5, 1, 5, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 6, 2, 6, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	//������ ������ ����.
	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 7, 1, 7, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 8, 5, 8, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 9, 3, 9, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 1, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 1, 2, 1, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	//������ ������ ����.
	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 2, 1, 2, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 3, 5, 3, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 4, 3, 4, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));
}

void BabyMonkey::Release()
{

}

void BabyMonkey::Update()
{

}

void BabyMonkey::Render(HDC hdc)
{

}

