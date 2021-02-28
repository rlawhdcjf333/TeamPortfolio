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

	mChampEx = L"�Ϳ��� ��Ÿ �Ƚ�. ���������� ���Ÿ� ���� crwod cc�� Ưȭ�� è��.";

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
	mSkill = 0;									//�������� ���� 
	mSpecialSkill = 100;

	//�ִϸ��̼�
	Animation* RightIdle = new Animation();											//������ �����
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

void StarPixie::Update()		//������ Ư�� : ��ų�� ����� �� �ణ�� �����ð��� �ִ�. (�׸�ŭ ������� ����)
{
	Champ::Update();
	mSkill += Time::GetInstance()->DeltaTime();		//DeltaTime���� �޾Ƽ� ����
	

	if (mTimer >= mSkillCasting)
	{
		//���� �̹����� ������ ������.
		//���� �̹����� Enemy�� ��Ƶ� ������� �ʴ´�.
		//�� �� ������ ������� �޸� �����Ѵ�.
		

		mTimer = 0;
	}

	if (mMP >= mSpecialSkill)	//�������� �������� Ư�������� ���� �Ͽ��� �� �ñر� �ߵ�.
	{
		//ĳ���� �ð���ŭ �ƹ������۵� �����ʰ� �ִϸ��̼Ǹ� �۵��Ѵ�.
		//ĳ���� �ð��� ������ �� �ñر⸦ ����Ѵ�.
		mMP = 0;	//0���� �ʱ�ȭ
	}
}

void StarPixie::Render(HDC hdc)
{

}

