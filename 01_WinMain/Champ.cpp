#include "pch.h"
#include "Champ.h"
#include "Animation.h"
#include "Staff.h"

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

void Champ::StaffOnChamp()
{
	Staff* staff = (Staff*)mStaff;

	mAtk += staff->GetAtk();
	mDef += staff->GetDef();

	auto list = staff->GetMostChamp();
	
	if (list.begin()->first == mName)
	{
		mAtk += list.begin()->second;
		mDef += list.begin()->second;
		mHP += list.begin()->second * 10;
		mFullHP += list.begin()->second * 10;
	}

	if (list.rbegin()->first == mName)
	{
		mAtk += list.rbegin()->second;
		mDef += list.rbegin()->second;
		mHP += list.rbegin()->second * 10;
		mFullHP += list.rbegin()->second * 10;
	}

	switch (staff->GetChar1())
	{
	case Character::Normal:
		break;
		
	case Character::Distraction:
		break;

	case Character::Fast:
		mSkill1Cool = 0.9*mSkill1Cool;
		break;

	case Character::Glass:
		
		break;

	case Character::Hero:
		break;
	case Character::Spear:
		break;

	case Character::Winner:
		break;

	case Character::None:
		break;

	case Character::Thorn:
		break;

	}


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
