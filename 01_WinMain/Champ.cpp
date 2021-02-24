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
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//�ִϸ��̼�
	/////////////////////////////////////////////////////////////////////
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 1, 3, 1, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 3, 4, 3, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* RightAttack = new Animation();
	RightAttack->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightAttack->SetIsLoop(true);
	RightAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 3, 0, true);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 2, 4, 2, true);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* LeftAttack = new Animation();
	LeftAttack->InitFrameByStartEnd(0, 2, 4, 2, true);
	LeftAttack->SetIsLoop(true);
	LeftAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 2, 4, 2, true);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 2, 4, 2, true);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 2, 4, 2, true);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));
	/////////////////////////////////////////////////////////////////
	
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



	//{{������ Ÿ���� ��Ÿ� �ȿ� ��� �´ٸ� �ñر� > ��ų > ���� ������ �ൿ�� �ϰ��Ѵ�.
	if (mRange <= mTargetDistance)	//Ÿ���� ��Ÿ� �ȿ� �ִ�.
	{
		if (mX < mTarget->GetX())//Ÿ���� �����ʿ� �ִ�
		{
			if (mMP >= mSkill1Cool)//������ �̻��� �ִٸ�
			{
				mCurrentAnm->Stop();
				mCurrentAnm = mAnimationList.find(L"RightSkill2")->second; //��ų2 ����� �����Ѵ�.
				mCurrentAnm->Play();

				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//�ñر� ��ų�� �������� ���� ���ٸ� Ÿ���� HP�� �������� �������� ��� ����� ���̵�� �ٲ۴�.
				{
					tmp->SetHP(tmp->GetHP() - 100);			//HP�� ��´�.
					mMP = 0;								//������ 0���� �ʱ�ȭ
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//����� ���̵�� �Ѵ�.
					mCurrentAnm->Play();
				}
			}
			else
			{
				if (mSkill1Cool <= 0)	//������ ���� ��ų���� 0���� �Ʒ����
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightSkill1")->second;//��ų1 ����� �����Ѵ�.
					mCurrentAnm->Play();

					if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
					{
						tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
						mSkill1Cool = 5;				//��Ÿ���� ������� �ʱ�ȭ
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//����� ���̵�� �Ѵ�.
						mCurrentAnm->Play();
					}
				}
				else
				{
					if (mAttackCool <= 0)	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightAttack")->second;//���� ����� �����Ѵ�.
						mCurrentAnm->Play();

						if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
						{
							tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
							mAttackCool = 5;				//��Ÿ���� ������� �ʱ�ȭ
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//����� ���̵�� �Ѵ�.
							mCurrentAnm->Play();
						}
					}
					else	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ��� �ƴ϶�� ���̵� ���·� �ٲ���
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
						mCurrentAnm->Play();
					}
				}
			}
		}

		else if (mX > mTarget->GetX())	//Ÿ���� ���ʿ� �ִٸ�
		{
			if (mMP >= 100)//������	100�̻��� �ִٸ�
			{
				mCurrentAnm->Stop();
				mCurrentAnm = mAnimationList.find(L"LeftSkill2")->second; //��ų2 ����� �����Ѵ�.
				mCurrentAnm->Play();

				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//�ñر� ��ų�� �������� ���� ���ٸ� Ÿ���� HP�� �������� �������� ��� ����� ���̵�� �ٲ۴�.
				{
					tmp->SetHP(tmp->GetHP() - 100);			//HP�� ��´�.
					mMP = 0;								//������ 0���� �ʱ�ȭ
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//����� ���̵�� �Ѵ�.
					mCurrentAnm->Play();
				}
			}
			else
			{
				if (mSkill1Cool <= 0)	//������ ���� ��ų���� 0���� �Ʒ����
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftSkill1")->second;//��ų1 ����� �����Ѵ�.
					mCurrentAnm->Play();

					if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
					{
						tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
						mSkill1Cool = 5;				//��Ÿ���� ������� �ʱ�ȭ
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//����� ���̵�� �Ѵ�.
						mCurrentAnm->Play();
					}
				}
				else
				{
					if (mAttackCool <= 0)	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftAttack")->second;//���� ����� �����Ѵ�.
						mCurrentAnm->Play();

						if (mCurrentAnm->GetCurrentFrameIndex() == 6)//��ų1�� �� ������ ���� ���ٸ� Ÿ���� HP�� �������� ���� �� ��� ����� ���̵�� �ٲ۴�.
						{
							tmp->SetHP(tmp->GetHP() - 100);	//HP�� ��´�.
							mAttackCool = 5;				//��Ÿ���� ������� �ʱ�ȭ
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//����� ���̵�� �Ѵ�.
							mCurrentAnm->Play();
						}
					}
					else	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ��� �ƴ϶�� ���̵� ���·� �ٲ���
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
						mCurrentAnm->Play();
					}
				}
			}
		}
		//}}

		//}}
	}

	else//{{��Ÿ� �ȿ� Ÿ���� ���ٸ�
	{
		if (mX < mTarget->GetX())	//Ÿ���� �����ʿ� �ִٸ�
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"RightRun")->second;	//����� ������ ������ �Ѵ�.
			mCurrentAnm->Play();

		}
		else if (mX > mTarget->GetX())	//Ÿ���� ���ʿ� �ִٸ�
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"LeftRun")->second;	//����� ���� ������ �Ѵ�.
			mCurrentAnm->Play();
		}

		mX += cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;	//�̵��ӵ���ŭ X,Y���� ���� ���Ѵ�.
		mY -= sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
	}

	//���� ��� �˰���
	mMPSecGet += Time::GetInstance()->DeltaTime();
	if (mMPSecGet >= 5)
	{
		mMPSecGet = 0;
		mMP += 20;
	}

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
