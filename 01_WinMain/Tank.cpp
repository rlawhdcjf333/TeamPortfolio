#include "pch.h"
#include "Tank.h"
#include "Animation.h"

Tank::Tank(const string& name)
	:Champ(name) 
{
	mChampName = L"Tank";
	mClassType = ClassType::ADCarry;
}

void Tank::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Tank", Resources(L"Tan.bmp"), 750, 700, 5, 10, true);
	mImage = IMAGEMANAGER->FindImage(L"Tank");
	//mFullHP;
	//mHP;
	//mMP;
	////mMPtmp;
	//mAtk;
	//mDef;
	//mDistance1;
	//mDistance2;
	//mDistance3;
	//mTargetDistance;
	//mAngle;
	//mRange;
	//mSpeed;
}

void Tank::Release()
{

}

void Tank::Update()
{
	Champ::Update();
}

void Tank::Render(HDC hdc)
{

}

