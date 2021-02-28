#include "pch.h"
#include "Tank.h"
#include "Animation.h"
#include "Image.h"

Tank::Tank()
	:Champ("Tank") {}

Tank::Tank(string str, float x, float y)
	: Champ(str)
{
	mX = x;
	mY = y;
	mRespawnX = x;
	mRespawnY = y;
}
Tank::Tank(string str)
	:Champ(str){}

void Tank::Init()
{
	//is action �� Ʈ��� �ٸ� �ൿ ���ϰ� �ؾߵ�
	//�̹��� �ε��ϰ� �ֱ�
	IMAGEMANAGER->LoadFromFile(L"Tank", Resources(L"Tank.bmp"), 750, 700, 5, 10, true);
	IMAGEMANAGER->LoadFromFile(L"HPBar", Resources(L"hpmpbar.bmp"), 90, 15, true);
	IMAGEMANAGER->LoadFromFile(L"HP", Resources(L"hp.bmp"), 88, 8, true);
	IMAGEMANAGER->LoadFromFile(L"MP", Resources(L"mp.bmp"), 80, 8, true);
	IMAGEMANAGER->LoadFromFile(L"exclamation", Resources(L"exclamation.bmp"), 40, 40, true);
	IMAGEMANAGER->LoadFromFile(L"Def", Resources(L"Def.bmp"), 20, 20, true);
	mImage = IMAGEMANAGER->FindImage(L"Tank");
	mHPBar = IMAGEMANAGER->FindImage(L"HPBar");
	mHPImage = IMAGEMANAGER->FindImage(L"HP");
	mMPImage = IMAGEMANAGER->FindImage(L"MP");
	mExclamation = IMAGEMANAGER->FindImage(L"exclamation");
	mDefImage = IMAGEMANAGER->FindImage(L"Def");

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"TankSkill", Resources(L"SkillIcon/TankSkill.bmp"), 62, 62, true);
	mSkillImage = IMAGEMANAGER->FindImage(L"TankSkill");

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"TankSpecialSkill", Resources(L"SkillIcon/TankSpecialSkill.bmp"), 62, 62, true);
	mSpecialSkillImage = IMAGEMANAGER->FindImage(L"TankSpecialSkill");

	mChampEx = L"�콺�ν����� ���������� ���۵� ����. ������ ���� �콺�ν����� �ʴ�.";
	mSkillEx = L"�ϳ��� ������ ������ ������ ���Ѵ�.";
	mSpecialSkillEx = L"�����带 �����Ͽ� ��Ÿ��� �þ�� ���ݷ��� ����Ѵ�. ���� ������ ������������ �ٲ�� ��ų���� �˹��� ��Ų��.";


	
	//���� �ʱ�ȭ
	mMaxHP = 80;
	mMaxMP = 100;
	mHP = mMaxHP;
	mMP = 0;
	mInitAtk = 15;
	mAtk = mInitAtk;
	mInitDef = 10;
	mDef = mInitDef;
	mSpeed = 110;
	mInitRange = 160;
	mRange = mInitRange;
	mMaxAttackCool = 1.5f;
	mAttackCool = 0;
	mMaxSkill1Cool = 5;
	mSkill1Cool = mMaxSkill1Cool;
	mDeathCool = 3;

	mDistance1 = 0;
	mDistance2 = 0;
	mDistance3 = 0;
	mAlpha = 0.6;

	mAngle = 0;
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	//�ִϸ��̼�
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 5, 4, 5, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 6, 4, 6, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* RightAttack = new Animation();
	RightAttack->InitFrameByStartEnd(0, 7, 2, 7, true);
	RightAttack->SetIsLoop(true);
	RightAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 7, 2, 7, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 8, 4, 8, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 9, 0, 9, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 4, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 1, 4, 1, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* LeftAttack = new Animation();
	LeftAttack->InitFrameByStartEnd(0, 2, 2, 2, false);
	LeftAttack->SetIsLoop(true);
	LeftAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 2, 2, 2, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 3, 4, 3, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 4, 0, 4, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));


	//���
	Animation* RightModeIdle = new Animation();
	RightModeIdle->InitFrameByStartEnd(4, 8, 4, 8, true);
	RightModeIdle->SetIsLoop(true);
	RightModeIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightModeIdle", RightModeIdle));

	Animation* RightModeShoot = new Animation();
	RightModeShoot->InitFrameByStartEnd(0, 8, 4, 8, true);
	RightModeShoot->SetIsLoop(true);
	RightModeShoot->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightModeShoot", RightModeShoot));

	Animation* RightModeShoot2 = new Animation();
	RightModeShoot2->InitFrameByStartEnd(0, 8, 4, 8, true);
	RightModeShoot2->SetIsLoop(true);
	RightModeShoot2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightModeShoot2", RightModeShoot2));

	Animation* LeftModeIdle = new Animation();
	LeftModeIdle->InitFrameByStartEnd(0, 3, 0, 3, false);
	LeftModeIdle->SetIsLoop(true);
	LeftModeIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftModeIdle", LeftModeIdle));

	Animation* LeftModeShoot = new Animation();
	LeftModeShoot->InitFrameByStartEnd(0, 3, 4, 3, false);
	LeftModeShoot->SetIsLoop(true);
	LeftModeShoot->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftModeShoot", LeftModeShoot));

	Animation* LeftModeShoot2 = new Animation();
	LeftModeShoot2->InitFrameByStartEnd(0, 3, 4, 3, false);
	LeftModeShoot2->SetIsLoop(true);
	LeftModeShoot2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftModeShoot2", LeftModeShoot2));
	//
	mapIter = mAnimationList.begin();
}

void Tank::Release()
{

}
void Tank::Update()
{
	Champ::Update();

	if (mIsDeath == true && mDeathCool <= 0)
	{
		mX = mRespawnX;	//��Ȱ���� �� ������ ��ҷ� �ʱ�ȭ ������
		mY = mRespawnY;
		mDeathCool = 3;
		mHP = mMaxHP;
		mAlpha = 0.6;
		mIsDeath = false;
		mIsAction = false;
	}
	if (Input::GetInstance()->GetKeyUp(VK_SPACE))
	{
		mHP -= 10;
	}

	if (mHP <= 0)
	{
		mIsDeath = true;
	}

	if (mIsDeath == true)
	{
		if (mCurrentAnm->GetNowFrameY() >= 5 && mCurrentAnm != mAnimationList.find(L"RightDeath")->second)
		{
			mDeathCount++;
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"RightDeath")->second;
			mCurrentAnm->Play();

		}
		if (mCurrentAnm->GetNowFrameY() < 5 && mCurrentAnm != mAnimationList.find(L"LeftDeath")->second)
		{
			mDeathCount++;
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"LeftDeath")->second;
			mCurrentAnm->Play();
		}

		mCurrentAnm->Update();
		mAlpha -= 0.2*Time::GetInstance()->DeltaTime();
		mDeathCool -= Time::GetInstance()->DeltaTime();
		return;
	}

	//������ ������ ���°� ��Ƽ���� �ֵ��� �Ÿ��� ã�Ƽ� ����� �ְ� Ÿ���� �ǰ� �����Ѵ�.
	//�켱 ��Ƽ�갡 Ʈ������ �������� Ȯ���� Ʈ��� ���� �־��ְ� �ƴϸ� 0�� �־ �Ÿ����� ���ϰ� �Ѵ�.
	//������ �� �Ÿ��� ����� �ָ� Ÿ������ �Ѵ�.
	if (mCurrentAnm != mAnimationList.find(L"RightSkill2")->second && mCurrentAnm != mAnimationList.find(L"LeftSkill2")->second)
		mMP += Time::GetInstance()->DeltaTime() * 7;	//MP 1�� �����ֱ�
	if (mCurrentAnm != mAnimationList.find(L"RightSkill1")->second && mCurrentAnm != mAnimationList.find(L"LeftSkill1")->second)
		mSkill1Cool -= Time::GetInstance()->DeltaTime(); //��ų �� ���ư��� ���ֱ�
	if (mCurrentAnm != mAnimationList.find(L"RightAttack")->second && mCurrentAnm != mAnimationList.find(L"LeftAttack")->second)
		mAttackCool -= Time::GetInstance()->DeltaTime(); //���� �� ���ư��� ���ֱ�

	if (mEnemyList.size() <= 0)
	{
		if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
		{
			mCurrentAnm->Stop();
			mapIter++;
			if (mapIter == mAnimationList.end())			//�̹��� �������� ���� ���
			{
				mapIter = mAnimationList.begin();
			}
			mCurrentAnm = mapIter->second;
			mCurrentAnm->Play();


		}
		mCurrentAnm->Update();
		mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
		return;
	}
	//{{�� �����ϱ� (���Ͻ� + Ÿ�����)
	vector<Champ*>temp;
	for (int i = 0; i < 3; i++)
	{
		Champ* tmp = (Champ*)mEnemyList[i];			//�ٿ�ĳ�����ؼ� isdeath�� �׾����� Ȯ�� 
		temp.push_back(tmp);
	}
	if (temp[0]->GetIsDeath() == false)
		mDistance1 = Math::GetDistance(mX, mY, mEnemyList[0]->GetX(), mEnemyList[0]->GetY());
	else mDistance1 = 1280;

	if (temp[1]->GetIsDeath() == false)
		mDistance2 = Math::GetDistance(mX, mY, mEnemyList[1]->GetX(), mEnemyList[1]->GetY());
	else mDistance2 = 1280;

	if (temp[2]->GetIsDeath() == false)
		mDistance3 = Math::GetDistance(mX, mY, mEnemyList[2]->GetX(), mEnemyList[2]->GetY());
	else mDistance3 = 1280;

	if (mProvocateur != true)
	{
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
	}
	else
	{
		mTargetDistance = Math::GetDistance(mX, mY, mTarget->GetX(), mTarget->GetY());
	}

	Champ* tmp = (Champ*)mTarget;		//Ÿ���� Ȯ�������� �� ü�¼����� ���� �ٿ�ĳ�����ع���
	mAngle = Math::GetAngle(mX, mY, mTarget->GetX(), mTarget->GetY());
	//}}

	//}}������ ������ ��ũ�� ���� �ٲ۴�.
	if (mMP >= 100)Mode(10, 140, 15);
	if (mIsMode == true)
	{
		mMP = 0;
		if (mAtk == mInitAtk)
		{
			mAtk = mAtk + mAtkBuff;
		}
		if (mRange == mInitRange)
		{
			mRange = mRange + mRangeBuff;
		}
		mModeTime -= Time::GetInstance()->DeltaTime();
		if (mModeTime <= 0)
		{
			mAtk = mAtk - mAtkBuff;
			mRange = mRange - mRangeBuff;
			mCurrentAnm->Stop();
			if (mCurrentAnm->GetNowFrameY() >= 5)
			{
				mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
				mCurrentAnm->Play();
			}
			else
			{
				mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
				mCurrentAnm->Play();
			}
			mIsMode = false;
		}
	}
	//}}

	//{{������ Ÿ���� ��Ÿ� �ȿ� ��� �´ٸ� �ñر� > ��ų > ���� ������ �ൿ�� �ϰ��Ѵ�.
	if (!(temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true)) //��� ������� ���� �۵�
	{
		if (mRange >= mTargetDistance && mIsAction == false)	//Ÿ���� ��Ÿ� �ȿ� �ִ�.
		{
			if (mX < mTarget->GetX())//Ÿ���� �����ʿ� �ִ�
			{
				if (!(mIsMode == true))
				{
					if (mSkill1Cool <= 0)	//������ ���� ��ų���� 0���� �Ʒ����
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightSkill1")->second;//��ų1 ����� �����Ѵ�.
						mCurrentAnm->Play();
						mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
					}
					else
					{
						if (mAttackCool <= 0)	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightAttack")->second;//���� ����� �����Ѵ�.
							mCurrentAnm->Play();
							mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
						}
						else if (mTargetDistance < mRange - 10)
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftRun")->second;
							mCurrentAnm->Play();

							mX -= cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
							mY += sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
						}
						else
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
							mCurrentAnm->Play();
							mIsAction = true;
						}
					}

				}
				else if (mIsMode == true)
				{
					if (mSkill1Cool <= 0)	//��忡�� ��ų���� 0���� �Ʒ����
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightModeShoot2")->second;//��ų1 ����� �����Ѵ�.
						mCurrentAnm->Play();
						mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
					}
					else
					{
						if (mAttackCool <= 0)	//��忡�� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightModeShoot")->second;//���� ����� �����Ѵ�.
							mCurrentAnm->Play();
							mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
						}
						else
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightModeIdle")->second;
							mCurrentAnm->Play();
							mIsAction = true;
						}
					}
				}
			}

			else if (mX > mTarget->GetX() && mIsAction == false)	//Ÿ���� ���ʿ� �ִٸ�
			{
				if (!(mIsMode == true))
				{
					if (mSkill1Cool <= 0)	//������ ���� ��ų���� 0���� �Ʒ����
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftSkill1")->second;//��ų1 ����� �����Ѵ�.
						mCurrentAnm->Play();
						mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
					}
					else
					{
						if (mAttackCool <= 0)	//������ ���� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftAttack")->second;//���� ����� �����Ѵ�.
							mCurrentAnm->Play();
							mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
						}
						else if (mTargetDistance < mRange - 10)
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightRun")->second;
							mCurrentAnm->Play();

							mX -= cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
							mY += sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;

						}
						else
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
							mCurrentAnm->Play();
							mIsAction = true;
						}
					}
				}
				else if (mIsMode == true)
				{
					if (mSkill1Cool <= 0)	//��忡�� ��ų���� 0���� �Ʒ����
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftModeShoot2")->second;//��ų1 ����� �����Ѵ�.
						mCurrentAnm->Play();
						mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
					}
					else
					{
						if (mAttackCool <= 0)	//��忡�� ��ų���� 0���� �Ʒ��� �ƴϰ� �������� 0���� �Ʒ����
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftModeShoot")->second;//���� ����� �����Ѵ�.
							mCurrentAnm->Play();
							mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
						}
						else
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftModeIdle")->second;
							mCurrentAnm->Play();
							mIsAction = true;
						}
					}
				}
			}
			else if (mX == mTarget->GetX() && mIsAction == false)
			{

			}
			//}}

			//}}
		}
		else if (mRange < mTargetDistance && mIsAction == false)//{{��Ÿ� �ȿ� Ÿ���� ���ٸ�
		{
			if (mX <= mTarget->GetX())	//Ÿ���� �����ʿ� �ִٸ�
			{
				if (mCurrentAnm != mAnimationList.find(L"RightRun")->second)
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightRun")->second;	//����� ������ ������ �Ѵ�.
					mCurrentAnm->Play();
				}
			}
			else if (mX > mTarget->GetX())	//Ÿ���� ���ʿ� �ִٸ�
			{
				if (mCurrentAnm != mAnimationList.find(L"LeftRun")->second)
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftRun")->second;	//����� ���� ������ �Ѵ�.
					mCurrentAnm->Play();
				}
			}


			if (!(temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true && mIsMode == true))	//��� �׾��� �� �� �����̰� �Ѵ�.
			{
				mX += cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;	//�̵��ӵ���ŭ X,Y���� ���� ���Ѵ�.
				mY -= sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
			}
			mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
		}


		//{{� ����� ������ ��
		if (mIsAction == true)
		{
			if (mCurrentAnm == mAnimationList.find(L"RightSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 2
				|| mCurrentAnm == mAnimationList.find(L"LeftSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 2)
			{
				//HP�� ����� � �� ���� �Ŀ� ����׼� ������
				tmp->SetHP(tmp->GetHP() - (mAtk *1.5*(1 - (tmp->GetDef() / (tmp->GetDef() + 30)))));
				mSkill1Cool = 5;
				mIsAction = false;
			}
			if ((mCurrentAnm == mAnimationList.find(L"RightAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 2)
				|| (mCurrentAnm == mAnimationList.find(L"LeftAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 2))
			{
				//HP�� ����� � �� ���� �Ŀ� ����׼� ������
				tmp->SetHP(tmp->GetHP() - (mAtk *(1 - (tmp->GetDef() / (tmp->GetDef() + 30)))));
				mAttackCool = mMaxAttackCool;
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 4
				|| mCurrentAnm == mAnimationList.find(L"LeftIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 4)
			{
				//HP�� ����� � �� ���� �Ŀ� ����׼� ������
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightModeShoot2")->second && mCurrentAnm->GetCurrentFrameIndex() == 4
				|| mCurrentAnm == mAnimationList.find(L"LeftModeShoot2")->second && mCurrentAnm->GetCurrentFrameIndex() == 4)
			{
				//HP�� ����� � �� ���� �Ŀ� ����׼� ������
				POINT pt = { temp[0]->GetX(), temp[0]->GetY() };
				POINT pt1 = { temp[1]->GetX(), temp[1]->GetY() };		//���� Ÿ���� ���� ����Ʈ ����
				POINT pt2 = { temp[2]->GetX(), temp[2]->GetY() };
				RECT rc = { mTarget->GetX() - 50,mTarget->GetY() - 50,mTarget->GetX() + 50,mTarget->GetY() + 50 };		//���� ��Ʈ ����

				float Angle = Math::GetAngle(mX, mY, temp[0]->GetX(), temp[0]->GetY());
				float Angle1 = Math::GetAngle(mX, mY, temp[1]->GetX(), temp[1]->GetY());
				float Angle2 = Math::GetAngle(mX, mY, temp[2]->GetX(), temp[2]->GetY());

				if (PtInRect(&rc, pt))
				{
					temp[0]->NuckBack(400, Angle);
					temp[0]->SetHP(temp[0]->GetHP() - (mAtk * (1 - (temp[0]->GetDef() / (temp[0]->GetDef() + 30)))));
				}
				if (PtInRect(&rc, pt1))
				{
					temp[1]->NuckBack(400, Angle1);
					temp[1]->SetHP(temp[1]->GetHP() - (mAtk * (1 - (temp[1]->GetDef() / (temp[1]->GetDef() + 30)))));
				}
				if (PtInRect(&rc, pt2))
				{
					temp[2]->NuckBack(400, Angle2);
					temp[2]->SetHP(temp[2]->GetHP() - (mAtk * (1 - (temp[2]->GetDef() / (temp[2]->GetDef() + 30)))));
				}
				mSkill1Cool = mMaxSkill1Cool;
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightModeShoot")->second && mCurrentAnm->GetCurrentFrameIndex() == 4
				|| mCurrentAnm == mAnimationList.find(L"LeftModeShoot")->second && mCurrentAnm->GetCurrentFrameIndex() == 4)
			{
				//HP�� ����� � �� ���� �Ŀ� ����׼� ������
				POINT pt = { temp[0]->GetX(), temp[0]->GetY() };
				POINT pt1 = { temp[1]->GetX(), temp[1]->GetY() };		//���� Ÿ���� ���� ����Ʈ ����
				POINT pt2 = { temp[2]->GetX(), temp[2]->GetY() };
				RECT rc = { mTarget->GetX() - 50,mTarget->GetY() - 50,mTarget->GetX() + 50,mTarget->GetY() + 50 };		//���� ��Ʈ ����

				if (PtInRect(&rc, pt))
				{
					temp[0]->SetHP(temp[0]->GetHP() - (mAtk *0.8* (1 - (temp[0]->GetDef() / (temp[0]->GetDef() + 30)))));
				}
				if (PtInRect(&rc, pt1))
				{
					temp[1]->SetHP(temp[1]->GetHP() - (mAtk *0.8* (1 - (temp[1]->GetDef() / (temp[1]->GetDef() + 30)))));
				}
				if (PtInRect(&rc, pt2))
				{
					temp[2]->SetHP(temp[2]->GetHP() - (mAtk *0.8* (1 - (temp[2]->GetDef() / (temp[2]->GetDef() + 30)))));
				}
				mAttackCool = mMaxAttackCool;
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightModeIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 0
				|| mCurrentAnm == mAnimationList.find(L"LeftModeIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 0)
			{
				mIsAction = false;
			}
		}
	}
	//}}

	//���� ��� �׾����� �� ���̵� ���·� �����.
	if (temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true)
	{
		if (mCurrentAnm->GetNowFrameY() >= 5 && mCurrentAnm != mAnimationList.find(L"RightIdle")->second)
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
			mCurrentAnm->Play();

		}
		else if (mCurrentAnm->GetNowFrameY() < 5 && mCurrentAnm != mAnimationList.find(L"LeftIdle")->second)
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
			mCurrentAnm->Play();
		}
	}

	//}}����
	//����� ������ ���� ����������
	if (mX <= 270) mX = 270;
	if (mX >= 1000) mX = 1000;
	if (mY <= 227) mY = 227;
	if (mY >= 640) mY = 640;

	if (mHP >= mMaxHP)mHP = mMaxHP;
	if (mMP >= mMaxMP)mMP = mMaxMP;
	mCurrentAnm->Update();
	mRect = RectMake(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	//}}

}
void Tank::Render(HDC hdc)
{
	//RenderRect(hdc, mRect);
	if (mCurrentAnm->GetNowFrameY() >= 5)
	{
		if (mCurrentAnm->GetNowFrameY() == 9)
		{
			mImage->AlphaScaleFrameRender(hdc, mX - 60, mY - 40, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 120, 56, mAlpha);
		}
		else
			mImage->ScaleFrameRender(hdc, mX - 60, mY - 40, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 120, 56);
	}
	else
	{
		if (mCurrentAnm->GetNowFrameY() == 4)
		{
			mImage->AlphaScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2 + 28, mY - 40, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 120, 56, mAlpha);
		}
		else
			mImage->ScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2 + 28, mY - 40, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 120, 56);
	}

	wstring atkCool = to_wstring(mRange);
	TextOut(hdc, 50, 100, atkCool.c_str(), atkCool.size());
	wstring atk = to_wstring(mAtk);
	TextOut(hdc, 50, 100, atk.c_str(), atk.size());
	if (mIsDeath != true)
	{
		mHPImage->Render(hdc, mX - 37, mY + 20, 0, 0, 88 * (mHP / mMaxHP), 8);
		mMPImage->Render(hdc, mX - 35, mY + 26, 0, 0, 80 * (mMP / mMaxMP), 8);
		mHPBar->Render(hdc, mX - 38, mY + 20);
	}
	if (mProvocateur)
	{
		if (mCurrentAnm->GetNowFrameY() >= 5)
			mExclamation->Render(hdc, mX - 37, mY - 50);
		else
			mExclamation->Render(hdc, mX + 4, mY - 50);
	}

	if (mGetDefBuff)
	{
		if (mCurrentAnm->GetNowFrameY() >= 5)
			mDefImage->Render(hdc, mX - 38, mY);
		else
			mDefImage->Render(hdc, mX + 32, mY);
	}
}

void Tank::Mode(float time, float plusrange, float plusdamage)
{
	mIsMode = true;
	mModeTime = time;
	mAtkBuff = plusdamage;
	mRangeBuff = plusrange;
}
