#include "pch.h"
#include "Ranger.h"
#include "Animation.h"

Ranger::Ranger()
	:Champ("Ranger") {}


void Ranger::Init()
{
	//�̹��� �ε��ϰ� �ֱ�
	IMAGEMANAGER->LoadFromFile(L"Ranger", Resources(L"Ranger.bmp"), 840, 1680, 7, 14,  true);
	mImage= IMAGEMANAGER->FindImage(L"Ranger");

	//���� �ʱ�ȭ
	mHP = 100;
	mMP = 0;
	mAtk = 10;
	mDef = 0;
	mSpeed = 1;
	mRange = 100;
	mAttackCool = 2;
	mSkill1Cool = 5;

	mDistance1 = 0;
	mDistance2 = 0;
	mDistance3 = 0;

	mAngle = 0;
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

	//�ִϸ��̼�
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 1, 3, 1, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));

	Animation* LeftIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 0, 3, 0, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* RightRun = new Animation();
	RightIdle->InitFrameByStartEnd(0, 3, 4, 3, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* LeftRun = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* RightAttack = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* LeftAttack = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* RightSkill1 = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* LeftSkill1 = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* RightSkill2 = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* LeftSkill2 = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* RightDeath = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftDeath = new Animation();
	RightIdle->InitFrameByStartEnd(0, 2, 4, 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));


}

void Ranger::Release()
{
	
}
void Ranger::Update()
{

	if (mHP <= 0)
	{
		mIsActive = false;
	}
	//������ ������ ���°� ��Ƽ���� �ֵ��� �Ÿ��� ã�Ƽ� ����� �ְ� Ÿ���� �ǰ� �����Ѵ�.
	//�켱 ��Ƽ�갡 Ʈ������ �������� Ȯ���� Ʈ��� ���� �־��ְ� �ƴϸ� 0�� �־ �Ÿ����� ���ϰ� �Ѵ�.
	//������ �� �Ÿ��� ����� �ָ� Ÿ������ �Ѵ�.

	mMP += Time::GetInstance()->DeltaTime();	//MP 1�� ����ֱ�
	mSkill1Cool -= Time::GetInstance()->DeltaTime(); //��ų �� ���ư��� ���ֱ�
	mAttackCool -= Time::GetInstance()->DeltaTime(); //���� �� ���ư��� ���ֱ�

	//{{���Ͻ� �ֱ�
	if(mEnemyList[0]->GetIsActive() ==true)
	mDistance1 = Math::GetDistance(mX, mY, mEnemyList[0]->GetX(), mEnemyList[0]->GetY());
	else mDistance1 = 0;

	if (mEnemyList[1]->GetIsActive() == true)
	mDistance2 = Math::GetDistance(mX, mY, mEnemyList[1]->GetX(), mEnemyList[1]->GetY());
	else mDistance2 = 0;

	if (mEnemyList[2]->GetIsActive() == true)
	mDistance3 = Math::GetDistance(mX, mY, mEnemyList[2]->GetX(), mEnemyList[2]->GetY());
	else mDistance3 = 0;

	if (mDistance1 < mDistance2 && mDistance1 < mDistance3)
	{
		mTarget = mEnemyList[0];
		mTargetDistance = mDistance1;
	}
	
	if (mDistance2 < mDistance3 && mDistance2 < mDistance1)
	{
		mTarget = mEnemyList[1];
		mTargetDistance = mDistance2;
	}

	if (mDistance3 < mDistance1 && mDistance3 < mDistance2)
	{
		mTarget = mEnemyList[2];
		mTargetDistance = mDistance3;
	}
	//Champ* tmp = (Champ*)mTarget;		//Ÿ���� Ȯ�������� �� ü�¼����� ���� �ٿ�ĳ�����ع���
	mAngle = Math::GetAngle(mX, mY, mTarget->GetX(), mTarget->GetY());
	//}}

	//{{������ Ÿ���� ��Ÿ� �ȿ� ��� �´ٸ� �ñر� > ��ų > ���� ������ �ൿ�� �ϰ��Ѵ�.
	if (mRange <= mTargetDistance)	//Ÿ���� ��Ÿ� �ȿ� �ִ�.
	{
		if (mX < mTarget->GetX())//Ÿ���� �����ʿ� �ִ�
		{
			if (mMP >= 100)//������	100�̻��� �ִٸ�
			{
				mCurrentAnm->Stop();
				mCurrentAnm = mAnimationList.find(L"RightSkill2")->second; //��ų2 ����� �����Ѵ�.
				mCurrentAnm->Play();

				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//�ñر� ��ų�� �������� ���� ���ٸ� Ÿ���� HP�� �������� �������� ��� ����� ���̵�� �ٲ۴�.
				{
					Champ* tmp = (Champ*)mTarget;			//Ÿ���� è���� �ٿ�ĳ����
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
						Champ* tmp = (Champ*)mTarget;	//Ÿ���� è���� �ٿ�ĳ����
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
							Champ* tmp = (Champ*)mTarget;	//Ÿ���� è���� �ٿ�ĳ����
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
					Champ* tmp = (Champ*)mTarget;			//Ÿ���� è���� �ٿ�ĳ����
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
						Champ* tmp = (Champ*)mTarget;	//Ÿ���� è���� �ٿ�ĳ����
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
							Champ* tmp = (Champ*)mTarget;	//Ÿ���� è���� �ٿ�ĳ����
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
		//}}
	}
	
	

	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	mCurrentAnm->Update();
}
void Ranger::Render(HDC hdc)
{

}