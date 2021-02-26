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

