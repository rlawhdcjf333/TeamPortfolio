#include "pch.h"
#include "BulletManager.h"
#include "Animation.h"

void BulletManager::Init(float startX,float startY, float endX, float endY)
{
	mX = startX;
	mY = startY;
	mEndX = endX;
	mEndY = endY;

	mAngle = Math::GetAngle(mX, mY, mEndX, mEndY);
	mSpeed = 500.f;
}

void BulletManager::Release()
{
}

void BulletManager::Update()
{
	mX += cosf(mAngle)*(Time::GetInstance()->DeltaTime())*mSpeed;	//이동속도만큼 X,Y값에 값을 더한다.
	mY -= sinf(mAngle)* (Time::GetInstance()->DeltaTime())* mSpeed;
	mRect = RectMakeCenter(mX / 10, mY / 10, mEndX / 10, mEndY / 10);
}

void BulletManager::Render(HDC hdc)
{
}
