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
	mSkill = 0;									//지역변수 선언 
	mSpecialSkill = 100;
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

