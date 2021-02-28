#include "pch.h"
#include "Champ.h"
#include "Animation.h"

enum class Motion
{
	Idle = 1,
	Run,
	Attack,
	Hit,
	Death
};

Champ::Champ(const string & name)
	:GameObject(name) {}

Champ::Champ(const string& name, float x, float y) : GameObject(name)
{
	mX = x, mY = y;
}

void Champ::Init()
{

}

void Champ::Release()
{

}

void Champ::Update()
{

}

void Champ::Render(HDC hdc)
{
	mImage->AlphaScaleFrameRender(hdc, mRect.left, mRect.top, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 100, 100, mAlpha);

}

void Champ::UIRender(HDC hdc, int startX, int startY, int width, int height)
{

	mImage->ScaleFrameRender(hdc, startX, startY, 0,0, width, height);

}

void Champ::ChampImageRender(HDC hdc, RECT rc)
{
	mImage->ScaleFrameRender(hdc, rc.left, rc.top, 0, 0, rc.right - rc.left, rc.bottom - rc.top);
}

void Champ::SkillImageRender(HDC hdc, RECT rc)
{
	mSkillImage->ScaleRender(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

void Champ::SpecialSkillImageRender(HDC hdc, RECT rc)
{
	mSpecialSkillImage->ScaleRender(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

//void Champ::GetStaff(string staff)
//{
//	//mStaff = ObjectManager::GetInstance()->FindObject(ObjectLayer::Staff, staff);
//}
//
//void Champ::GetEnemy(string enemy1, string enemy2, string enemy3)
//{
//	//mEnemy1 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, enemy1);
//	//mEnemy2 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, enemy2);
//	//mEnemy3 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, enemy3);
//}
//
//void Champ::GetFriendly(string friendly1, string friendly2)
//{
//	//mFriendly1 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, friendly1);
//	//mFriendly2 = ObjectManager::GetInstance()->FindObject(ObjectLayer::Champ, friendly2);
//}
