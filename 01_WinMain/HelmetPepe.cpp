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

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"PepeSkill", Resources(L"SkillIcon/PepeSkill.bmp"), 62, 62, true);
	mSkillImage = IMAGEMANAGER->FindImage(L"PepeSkill");

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"PepeSpecialSkill", Resources(L"SkillIcon/PepeSpecialSkill.bmp"), 62, 62, true);
	mSpecialSkillImage = IMAGEMANAGER->FindImage(L"PepeSpecialSkill");

	mChampEx = L"����� ������ �� ���. ������ �𸣰����� �������̴�.";
	mSkillEx = L"�ڽ� �ֺ��� ��븦 3�ʰ� �����Ѵ�.";
	mSpecialSkillEx = L"�������� �������� �߾� ��� �Ʊ��� ������ �����ð� �ø���.";

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
