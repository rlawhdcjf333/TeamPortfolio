#include "pch.h"
#include "Champ.h"
#include "Animation.h"

Champ::Champ(const string& name, float x, float y) : GameObject(name)
{
	mX = x, mY = y;
}

void Champ::Init()
{

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	RectMakeCenter(mX, mY, mSizeX, mSizeY);

}

void Champ::Release()
{

}

void Champ::Update()
{
	//Champ�� ����
}

void Champ::Render(HDC hdc)
{
	mImage->AlphaScaleFrameRender(hdc, mRect.left, mRect.top, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 100,100, mAlpha);

}

void Champ::SetEnemy(string enemy1, string enemy2, string enemy3)
{
	mEnemy1 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, enemy1);
	mEnemy2 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, enemy2);
	mEnemy3 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, enemy3);
}

void Champ::SetFriend(string friend1, string friend2)
{
	mFriend1 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, friend1);
	mFriend2 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, friend2);
}
