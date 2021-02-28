#include "pch.h"
#include "Yeti.h"
#include "Animation.h"

Yeti::Yeti(const string& name)
	:Champ(name) 
{
	mChampName = L"Yeti";
	mClassType = ClassType::Warrior;
}

void Yeti::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Yeti", Resources(L"Yeti.bmp"), 2700, 2760, 9, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"Yeti");

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

	mAttackCool = 1.f;
	mSkill1Cool = 100.f;
	mDeathCool = 3.f;
	mSkill = 0;									//�������� ���� 
	mSpecialSkill = 100;

	mChampEx = L"���������� ��ȭ�Ӱ� ������ ����. ưư�� ü�°� �˹����� �Ʊ��� �����ش�.";

	//�ִϸ��̼�
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 6, 2, 6, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 7, 3, 7, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* RightAttack = new Animation();
	RightAttack->InitFrameByStartEnd(0, 8, 5, 8, true);
	RightAttack->SetIsLoop(true);
	RightAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 9, 5, 9, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 10, 8, 10, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 2, 6, 2, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 2, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 1, 3, 1, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* LeftAttack = new Animation();
	LeftAttack->InitFrameByStartEnd(0, 2, 5, 2, false);
	LeftAttack->SetIsLoop(true);
	LeftAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 3, 5, 3, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 4, 8, 4, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 5, 6, 5, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));
}

void Yeti::Release()
{
}

void Yeti::Update()
{
	if (!mIsActive) return;				//

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

				if (mCurrentAnm->GetCurrentFrameIndex() == 9)//�ñر� ��ų�� �������� ���� ���ٸ� Ÿ���� HP�� �������� �������� ��� ����� ���̵�� �ٲ۴�.
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

void Yeti::Render(HDC hdc)
{
}
