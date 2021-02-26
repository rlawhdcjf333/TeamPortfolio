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

Champ::Champ(const string& name, int animation)
{
	mImageAnimationFrame = animation;
}

void Champ::Init()
{
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	
	
	Champ* tmp = (Champ*)mTarget;		//Ÿ���� Ȯ�������� �� ü�¼����� ���� �ٿ�ĳ�����ع���
	mAngle = Math::GetAngle(mX, mY, mTarget->GetX(), mTarget->GetY());

	mMPSecGet = 0;
	mDeathCool = 3;
}

void Champ::Release()
{

}

void Champ::Update()
{
	if (!mIsActive) return;

	if (mTarget == nullptr) return;


	Champ* tmp = (Champ*)mTarget;		//Ÿ���� Ȯ�������� �� ü�¼����� ���� �ٿ�ĳ�����ع���
	mAngle = Math::GetAngle(mX, mY, mTarget->GetX(), mTarget->GetY());

	if (mHP <= 0)											//�׾��� �� �˰��� 
	{
		mIsActive = false;
		if (mIsActive == false)
		{
			mDeathCool -= Time::GetInstance()->DeltaTime();
			if (mIsActive == false && mDeathCool <= 0)				//
			{
				mDeathCool = 3;
				mIsActive = true;
				//if(mName=="")
				//{ 
				//
				//}
				//else if (mName == "")
				//{
				//
				//}
				mHP = mFullHP;				//�� �׷��� ��� ĳ������ HP�� �Ȱ��� ���� ���̴� mHP = mCharacterHPMAX��� ���� ������ ����ؼ� �޾ƿ� �� �ְ� ������
			}							//�׷� Init �Ű������� float CharacterHPMAX��� ���� ��������� �ϴµ� �������̵尡 �Ǿ� ����� �� ����. 
		}								//��� �޾ƿ��°� ������? ���� ���������� �����ڸ� �̿��غ���� �߾��� �̰��� ��Ʈ�� �� ����.

	}



	////{{������ Ÿ���� ��Ÿ� �ȿ� ��� �´ٸ� �ñر� > ��ų > ���� ������ �ൿ�� �ϰ��Ѵ�.
	//if (mRange <= mTargetDistance)	//Ÿ���� ��Ÿ� �ȿ� �ִ�.
	//{
	//	if (mX < mTarget->GetX())//Ÿ���� �����ʿ� �ִ�
	//	{
	//		if (mMP >= mSkill1Cool)//������ �̻��� �ִٸ�
	//		{
	//			mCurrentAnm->Stop();
	//			mCurrentAnm = mAnimationList.find(L"RightSkill2")->second; //��ų2 ����� �����Ѵ�.
	//			mCurrentAnm->Play();
	//
	//			if (mCurrentAnm->GetCurrentFrameIndex() == mImage->FrameRender()//�ñر� ��ų�� �������� ���� ���ٸ� Ÿ���� HP�� �������� �������� ��� ����� ���̵�� �ٲ۴�.
	//			{
	//				tmp->SetHP(tmp->GetHP() - 100);			//HP�� ��´�.
	//					mMP = 0;								//������ 0���� �ʱ�ȭ
	//					mCurrentAnm->Stop();
	//					mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//����� ���̵�� �Ѵ�.
	//					mCurrentAnm->Play();
	//			}
	//		}
	//		else
	//		{
	//			if (mSkill1Cool <= 0)	//������ ���� ��ų���� 0���� �Ʒ����
	//			{
	//				mCurrentAnm->Stop();
	//				mCurrentAnm = mAnimationList.find(L"RightSkill1")->second;//��ų1 ����� �����Ѵ�.
	//				mCurrentAnm->Play();
	//
	//				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
	//				{
	//					tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
	//					mSkill1Cool = 5;				//��Ÿ���� ������� �ʱ�ȭ
	//					mCurrentAnm->Stop();
	//					mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//����� ���̵�� �Ѵ�.
	//					mCurrentAnm->Play();
	//				}
	//			}
	//			else
	//			{
	//				if (mAttackCool <= 0)	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
	//				{
	//					mCurrentAnm->Stop();
	//					mCurrentAnm = mAnimationList.find(L"RightAttack")->second;//���� ����� �����Ѵ�.
	//					mCurrentAnm->Play();
	//
	//					if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
	//					{
	//						tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
	//						mAttackCool = 5;				//��Ÿ���� ������� �ʱ�ȭ
	//						mCurrentAnm->Stop();
	//						mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//����� ���̵�� �Ѵ�.
	//						mCurrentAnm->Play();
	//					}
	//				}
	//				else	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ��� �ƴ϶�� ���̵� ���·� �ٲ���
	//				{
	//					mCurrentAnm->Stop();
	//					mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
	//					mCurrentAnm->Play();
	//				}
	//			}
	//		}
	//	}
	//
	//	else if (mX > mTarget->GetX())	//Ÿ���� ���ʿ� �ִٸ�
	//	{
	//		if (mMP >= 100)//������	100�̻��� �ִٸ�
	//		{
	//			mCurrentAnm->Stop();
	//			mCurrentAnm = mAnimationList.find(L"LeftSkill2")->second; //��ų2 ����� �����Ѵ�.
	//			mCurrentAnm->Play();
	//
	//			if (mCurrentAnm->GetCurrentFrameIndex() == 6)//�ñر� ��ų�� �������� ���� ���ٸ� Ÿ���� HP�� �������� �������� ��� ����� ���̵�� �ٲ۴�.
	//			{
	//
	//				tmp->SetHP(tmp->GetHP() - 100);			//HP�� ��´�.
	//				mMP = 0;								//������ 0���� �ʱ�ȭ
	//				mCurrentAnm->Stop();
	//				mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//����� ���̵�� �Ѵ�.
	//				mCurrentAnm->Play();
	//			}
	//		}
	//		else
	//		{
	//			if (mSkill1Cool <= 0)	//������ ���� ��ų���� 0���� �Ʒ����
	//			{
	//				mCurrentAnm->Stop();
	//				mCurrentAnm = mAnimationList.find(L"LeftSkill1")->second;//��ų1 ����� �����Ѵ�.
	//				mCurrentAnm->Play();
	//
	//				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
	//				{
	//					tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
	//					mSkill1Cool = 5;				//��Ÿ���� ������� �ʱ�ȭ
	//					mCurrentAnm->Stop();
	//					mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//����� ���̵�� �Ѵ�.
	//					mCurrentAnm->Play();
	//				}
	//			}
	//			else
	//			{
	//				if (mAttackCool <= 0)	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
	//				{
	//					mCurrentAnm->Stop();
	//					mCurrentAnm = mAnimationList.find(L"LeftAttack")->second;//���� ����� �����Ѵ�.
	//					mCurrentAnm->Play();
	//
	//					if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
	//					{
	//						tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
	//						mAttackCool = 5;				//��Ÿ���� ������� �ʱ�ȭ
	//						mCurrentAnm->Stop();
	//						mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//����� ���̵�� �Ѵ�.
	//						mCurrentAnm->Play();
	//					}
	//				}
	//				else	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ��� �ƴ϶�� ���̵� ���·� �ٲ���
	//				{
	//					mCurrentAnm->Stop();
	//					mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
	//					mCurrentAnm->Play();
	//				}
	//			}
	//		}
	//	}
	//	//}}
	//
	//	//}}
	//}
	//
	//else//{{��Ÿ� �ȿ� Ÿ���� ���ٸ�
	//{
	//	if (mX < mTarget->GetX())	//Ÿ���� �����ʿ� �ִٸ�
	//	{
	//		mCurrentAnm->Stop();
	//		mCurrentAnm = mAnimationList.find(L"RightRun")->second;	//����� ������ ������ �Ѵ�.
	//		mCurrentAnm->Play();
	//
	//	}
	//	else if (mX > mTarget->GetX())	//Ÿ���� ���ʿ� �ִٸ�
	//	{
	//		mCurrentAnm->Stop();
	//		mCurrentAnm = mAnimationList.find(L"LeftRun")->second;	//����� ���� ������ �Ѵ�.
	//		mCurrentAnm->Play();
	//	}
	//
	//	mX += cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;	//�̵��ӵ���ŭ X,Y���� ���� ���Ѵ�.
	//	mY -= sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
	//}
	//
	////���� ��� �˰���
	//mMPSecGet += Time::GetInstance()->DeltaTime();
	//if (mMPSecGet >= 5)
	//{
	//	mMPSecGet = 0;
	//	mMP += 20;
	//}

	//mPlayerList�� �ְ� mEnemyList

	// ������ �Ͽ��� �� ���� N���� ��� �ϴ� �˰���
	//if(Range���� �ȿ� mEnemyList�� ������ ���.)
	//AtkCool -= Time::GetInstance()->DeltaTime();			//Ex) AtkCool = 1.23f��.
	//if(AtkCool <= 0)
	//mMP += N;
	//mHP -= mAtk					//�ٸ� �������� mHP�� mAtk���� �������� �� ���̴�. (�÷��̾� ���ΰ� ���� ���ΰ�)
	//AtkCool = 1.23f				//�� ���⿡ �ִ� ���ڵ�, �� è���鸶�� ���ݼӵ��� �ٸ� ���̴� �Ű������� ���� �� �ְ� ������Ұ� ����.

	//���Ÿ� �˰���




	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCurrentAnm->Update();
	
}

void Champ::Render(HDC hdc)
{
	mImage->AlphaScaleFrameRender(hdc, mRect.left, mRect.top, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 100, 100, mAlpha);

}

void Champ::ChampImageRender(HDC hdc, RECT rc)
{
	mImage->ScaleFrameRender(hdc, rc.left, rc.top, 0, 0, rc.right - rc.left, rc.bottom - rc.top);
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
