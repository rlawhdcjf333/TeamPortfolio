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
	:GameObject(name), mIsAction(false), mIsDeath(false), mAggroTime(0), mIsAggro(false), mDeathCount(0) {}

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
	//앵글의 방향에 포스만큼 날아간다 포스가 줄어들다 0이되면 멈춘다. 
	if (mIsNuckback == true)
	{
		mX += cos(mNuckbackAngle)*mNuckbackForce*Time::GetInstance()->DeltaTime();
		mY -= sin(mNuckbackAngle)*mNuckbackForce*Time::GetInstance()->DeltaTime();
		mNuckbackForce -= 1000 * Time::GetInstance()->DeltaTime();
		if (mNuckbackForce <= 0)
		{
			mIsNuckback = false;
		}
	}

	if (mIsAtkBuff == true)
	{
		if (mAtk == mInitAtk)
			mAtk = mAtk + mAtkBuff;
		mAtkBuffTime -= Time::GetInstance()->DeltaTime();
		if (mAtkBuffTime <= 0)
		{
			mAtk = mInitAtk;
			mIsAtkBuff = false;
		}
	}

	if (mIsDefBuff == true)
	{
		vector<Champ*>temp;
		for (int i = 0; i < 3; i++)
		{
			Champ* tmp = (Champ*)mFriendList[i];
			temp.push_back(tmp);

		}
		if (mDef == mInitDef)
		{
			temp[0]->SetDef(temp[0]->GetDef() + mDefBuff);
			temp[1]->SetDef(temp[1]->GetDef() + mDefBuff);
			temp[2]->SetDef(temp[2]->GetDef() + mDefBuff);

			temp[0]->SetGetDefBuff(true);
			temp[1]->SetGetDefBuff(true);
			temp[2]->SetGetDefBuff(true);
		}

		mDefBuffTime -= Time::GetInstance()->DeltaTime();
		if (mDefBuffTime <= 0)
		{
			temp[0]->SetDef(temp[0]->GetDef() - mDefBuff);
			temp[1]->SetDef(temp[1]->GetDef() - mDefBuff);
			temp[2]->SetDef(temp[2]->GetDef() - mDefBuff);

			temp[0]->SetGetDefBuff(false);
			temp[1]->SetGetDefBuff(false);
			temp[2]->SetGetDefBuff(false);
		}
	}


	if (mIsAggro)
	{
		POINT pt = { mEnemyList[0]->GetX(), mEnemyList[0]->GetY() };
		POINT pt1 = { mEnemyList[1]->GetX(), mEnemyList[1]->GetY() };
		POINT pt2 = { mEnemyList[2]->GetX(), mEnemyList[2]->GetY() };
		RECT rc = { mX - 100,mY - 100,mX + 100,mY + 100 };

		vector<Champ*>temp;
		for (int i = 0; i < 3; i++)
		{
			Champ* tmp = (Champ*)mEnemyList[i];
			temp.push_back(tmp);

		}

		if (PtInRect(&rc, pt))
		{
			temp[0]->SetTarget(this);
			temp[0]->SetProvocateur(true);
		}
		if (PtInRect(&rc, pt1))
		{
			temp[1]->SetTarget(this);
			temp[1]->SetProvocateur(true);
		}
		if (PtInRect(&rc, pt2))
		{
			temp[2]->SetTarget(this);
			temp[2]->SetProvocateur(true);
		}
		mAggroTime -= Time::GetInstance()->DeltaTime();

		if (mAggroTime <= 0)
		{
			temp[0]->SetProvocateur(false);
			temp[1]->SetProvocateur(false);
			temp[2]->SetProvocateur(false);
			mIsAggro = false;
		}
	}
}

void Champ::Render(HDC hdc)
{
}

void Champ::UIRender(HDC hdc, int startX, int startY, int width, int height)
{

	mImage->ScaleFrameRender(hdc, startX, startY, 0, 0, width, height);

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
		mMaxHP += list.begin()->second * 10;
	}

	if (list.rbegin()->first == mName)
	{
		mAtk += list.rbegin()->second;
		mDef += list.rbegin()->second;
		mHP += list.rbegin()->second * 10;
		mMaxHP += list.rbegin()->second * 10;
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

void Champ::SkillImageRender(HDC hdc, RECT rc)
{
	mSkillImage->ScaleRender(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

void Champ::SpecialSkillImageRender(HDC hdc, RECT rc)
{
	mSpecialSkillImage->ScaleRender(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

void Champ::NuckBack(float force, float angle)
{
	mIsNuckback = true;
	mNuckbackForce = force;
	mNuckbackAngle = angle;
}

void Champ::AtkBuff(float atkbuff, float time)
{
	mIsAtkBuff = true;
	mAtkBuff = atkbuff;
	mAtkBuffTime = time;
}

void Champ::Aggro(float time)
{
	mIsAggro = true;
	mAggroTime = time;
}

void Champ::DefBuff(float defbuff, float time)
{
	mIsDefBuff = true;
	mDefBuff = defbuff;
	mDefBuffTime = time;
}


