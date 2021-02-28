#include "pch.h"
#include "Yeti.h"
#include "Animation.h"
#include "Image.h"

Yeti::Yeti()
	:Champ("Yeti") {}

Yeti::Yeti(string str, float x, float y)
	: Champ(str)
{
	mX = x;
	mY = y;
	mRespawnX = x;
	mRespawnY = y;
}

Yeti::Yeti(const string name)
	:Champ(name)
{
	mChampName = L"Yeti";
	mClassType = ClassType::Warrior;
}


void Yeti::Init()
{
	//�̹��� �ε��ϰ� �ֱ�
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Yeti", Resources(L"Yeti.bmp"), 2700, 2760, 9, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"Yeti");

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"YetiSkill", Resources(L"SkillIcon/YetiSkill.bmp"), 62, 62, true);
	mSkillImage = IMAGEMANAGER->FindImage(L"YetiSkill");

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"YetiSpecialSkill", Resources(L"SkillIcon/YetiSpecialSkill.bmp"), 62, 62, true);
	mSpecialSkillImage = IMAGEMANAGER->FindImage(L"YetiSpecialSkill");

	mChampEx = L"���������� ��ȭ�Ӱ� ������ ����. ưư�� ü�°� �˹����� �Ʊ��� �����ش�.";
	mSkillEx = L"�ڽ� �ֺ��� ��븦 �˹��Ű�� �����ð����� �ڽ��� ���ݷ��� ������Ų��.";
	mSpecialSkillEx = L"������ �ٶ��� ����� ��� �ڽ� �ֺ��� ��븦 ���ϰ� �˹��ϰ� ���������� �Ѵ�.";

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"YetiSpecialSkill", Resources(L"SkillIcon/YetiSpecialSkill.bmp"), 62, 62, true);
	mSpecialSkillImage = IMAGEMANAGER->FindImage(L"YetiSpecialSkill");

	IMAGEMANAGER->LoadFromFile(L"Yeti", Resources(L"Yeti.bmp"), 2700, 2760, 9, 12, true);
	IMAGEMANAGER->LoadFromFile(L"HPBar", Resources(L"hpmpbar.bmp"), 90, 15, true);
	IMAGEMANAGER->LoadFromFile(L"HP", Resources(L"hp.bmp"), 88, 8, true);
	IMAGEMANAGER->LoadFromFile(L"MP", Resources(L"mp.bmp"), 80, 8, true);
	IMAGEMANAGER->LoadFromFile(L"exclamation", Resources(L"exclamation.bmp"), 40, 40, true);
	IMAGEMANAGER->LoadFromFile(L"Def", Resources(L"Def.bmp"), 20, 20, true);
	mImage = IMAGEMANAGER->FindImage(L"Yeti");
	mHPBar = IMAGEMANAGER->FindImage(L"HPBar");
	mHPImage = IMAGEMANAGER->FindImage(L"HP");
	mMPImage = IMAGEMANAGER->FindImage(L"MP");
	mExclamation = IMAGEMANAGER->FindImage(L"exclamation");
	mDefImage = IMAGEMANAGER->FindImage(L"Def");
	//���� �ʱ�ȭ
	mMaxHP = 200;
	mMaxMP = 100;
	mHP = mMaxHP;
	mMP = 0;
	mInitAtk = 17;
	mAtk = mInitAtk;
	mInitDef = 5;
	mDef = mInitDef;
	mSpeed = 150;
	mRange = 60;
	mMaxAttackCool = 1.5;
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
	RightDeath->InitFrameByStartEnd(0, 11, 6, 11, true);
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

	mapIter = mAnimationList.begin();
}

void Yeti::Release()
{

}
void Yeti::Update()
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
		if (mCurrentAnm->GetNowFrameY() >= 6 && mCurrentAnm != mAnimationList.find(L"RightDeath")->second)
		{
			mDeathCount++;
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"RightDeath")->second;
			mCurrentAnm->Play();

		}
		if (mCurrentAnm->GetNowFrameY() < 6 && mCurrentAnm != mAnimationList.find(L"LeftDeath")->second)
		{
			mDeathCount++;
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"LeftDeath")->second;
			mCurrentAnm->Play();
		}
		if (mCurrentAnm->GetCurrentFrameIndex() != 6)
			mCurrentAnm->Update();
		mAlpha -= 0.2*Time::GetInstance()->DeltaTime();
		mDeathCool -= Time::GetInstance()->DeltaTime();
		return;
	}

	//������ ������ ���°� ��Ƽ���� �ֵ��� �Ÿ��� ã�Ƽ� ����� �ְ� Ÿ���� �ǰ� �����Ѵ�.
	//�켱 ��Ƽ�갡 Ʈ������ �������� Ȯ���� Ʈ��� ���� �־��ְ� �ƴϸ� 0�� �־ �Ÿ����� ���ϰ� �Ѵ�.
	//������ �� �Ÿ��� ����� �ָ� Ÿ������ �Ѵ�.
	if (mCurrentAnm != mAnimationList.find(L"RightSkill2")->second && mCurrentAnm != mAnimationList.find(L"LeftSkill2")->second)
		mMP += Time::GetInstance()->DeltaTime() * 7;	//MP 7�� �����ֱ�
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


	//{{������ Ÿ���� ��Ÿ� �ȿ� ��� �´ٸ� �ñر� > ��ų > ���� ������ �ൿ�� �ϰ��Ѵ�.
	if (!(temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true)) //��� ������� ���� �۵�
	{
		if (mRange >= mTargetDistance && mIsAction == false)	//Ÿ���� ��Ÿ� �ȿ� �ִ�.
		{
			if (mX < mTarget->GetX())//Ÿ���� �����ʿ� �ִ�
			{
				if (mMP >= 100)//������	100�̻��� �ִٸ�
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightSkill2")->second; //��ų2 ����� �����Ѵ�.
					mCurrentAnm->Play();
					mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.

				}
				else
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
						else
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
							mCurrentAnm->Play();
							mIsAction = true;
						}
					}
				}
			}

			else if (mX > mTarget->GetX() && mIsAction == false)	//Ÿ���� ���ʿ� �ִٸ�
			{
				if (mMP >= 100)//������	100�̻��� �ִٸ�
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftSkill2")->second; //��ų2 ����� �����Ѵ�.
					mCurrentAnm->Play();
					mIsAction = true;	//�׼��� Ʈ��� �ٲ۴�.
				}
				else
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
						else
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
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


			if (!(temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true))	//��� �׾��� �� �� �����̰� �Ѵ�.
			{
				mX += cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;	//�̵��ӵ���ŭ X,Y���� ���� ���Ѵ�.
				mY -= sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
			}
			mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
		}


		//{{� ����� ������ ��
		if (mIsAction == true)
		{
			if (mCurrentAnm == mAnimationList.find(L"RightSkill2")->second && mCurrentAnm->GetCurrentFrameIndex() == 6
				|| mCurrentAnm == mAnimationList.find(L"LeftSkill2")->second && mCurrentAnm->GetCurrentFrameIndex() == 6)
			{
				mMP = 0;

				POINT pt = { temp[0]->GetX(), temp[0]->GetY() };
				POINT pt1 = { temp[1]->GetX(), temp[1]->GetY() };		//���� Ÿ���� ���� ����Ʈ ����
				POINT pt2 = { temp[2]->GetX(), temp[2]->GetY() };
				RECT rc = { mX - 100,mY - 100,mX + 100,mY + 100 };		//���� ��Ʈ ����

				float Angle = Math::GetAngle(mX, mY, temp[0]->GetX(), temp[0]->GetY());
				float Angle1 = Math::GetAngle(mX, mY, temp[1]->GetX(), temp[1]->GetY());
				float Angle2 = Math::GetAngle(mX, mY, temp[2]->GetX(), temp[2]->GetY());

				if (PtInRect(&rc, pt))
				{
					temp[0]->NuckBack(600, Angle);
					temp[0]->SetHP(temp[0]->GetHP() - (mAtk *(1 - (temp[0]->GetDef() / (temp[0]->GetDef() + 30)))));
				}
				if (PtInRect(&rc, pt1))
				{
					temp[1]->NuckBack(600, Angle1);
					temp[1]->SetHP(temp[1]->GetHP() - (mAtk *(1 - (temp[1]->GetDef() / (temp[1]->GetDef() + 30)))));
				}
				if (PtInRect(&rc, pt2))
				{
					temp[2]->NuckBack(600, Angle2);
					temp[2]->SetHP(temp[2]->GetHP() - (mAtk *(1 - (temp[2]->GetDef() / (temp[2]->GetDef() + 30)))));
				}
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 5
				|| mCurrentAnm == mAnimationList.find(L"LeftSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 5)
			{
				mSkill1Cool = mMaxSkill1Cool;
				POINT pt = { temp[0]->GetX(), temp[0]->GetY() };
				POINT pt1 = { temp[1]->GetX(), temp[1]->GetY() };		//���� Ÿ���� ���� ����Ʈ ����
				POINT pt2 = { temp[2]->GetX(), temp[2]->GetY() };
				RECT rc = { mX - 100,mY - 100,mX + 100,mY + 100 };		//���� ��Ʈ ����

				float Angle = Math::GetAngle(mX, mY, temp[0]->GetX(), temp[0]->GetY());
				float Angle1 = Math::GetAngle(mX, mY, temp[1]->GetX(), temp[1]->GetY());
				float Angle2 = Math::GetAngle(mX, mY, temp[2]->GetX(), temp[2]->GetY());

				if (PtInRect(&rc, pt))
					temp[0]->NuckBack(400, mAngle);
				if (PtInRect(&rc, pt1))
					temp[1]->NuckBack(400, mAngle);
				if (PtInRect(&rc, pt2))
					temp[2]->NuckBack(400, mAngle);

				AtkBuff(10, 5);
				mIsAction = false;
			}
			if ((mCurrentAnm == mAnimationList.find(L"RightAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 5)
				|| (mCurrentAnm == mAnimationList.find(L"LeftAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 5))
			{
				mAttackCool = mMaxAttackCool;
				tmp->SetHP(tmp->GetHP() - (mAtk *(1 - (tmp->GetDef() / (tmp->GetDef() + 30)))));
				tmp->NuckBack(400, mAngle);
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 2
				|| mCurrentAnm == mAnimationList.find(L"LeftIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 2)
			{
				//HP�� ����� � �� ���� �Ŀ� ����׼� ������
				mIsAction = false;
			}
		}
	}
	//}}

	//���� ��� �׾����� �� ���̵� ���·� �����.
	if (temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true)
	{
		if (mCurrentAnm->GetNowFrameY() >= 6 && mCurrentAnm != mAnimationList.find(L"RightIdle")->second)
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"RightIdle")->second;
			mCurrentAnm->Play();

		}
		else if (mCurrentAnm->GetNowFrameY() < 6 && mCurrentAnm != mAnimationList.find(L"LeftIdle")->second)
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

	if (mHP > mMaxHP)mHP = mMaxHP;
	if (mMP > mMaxMP)mMP = mMaxMP;
	mCurrentAnm->Update();
	mRect = RectMake(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	//}}

}
void Yeti::Render(HDC hdc)
{
	//RenderRect(hdc, mRect);
	if (mCurrentAnm->GetNowFrameY() >= 6)
	{
		if (mCurrentAnm->GetNowFrameY() == 11)
		{
			mImage->AlphaScaleFrameRender(hdc, mX - 30, mY - 110, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 200, 130, mAlpha);
		}
		else
			mImage->ScaleFrameRender(hdc, mX - 30, mY - 110, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 200, 130);
	}
	else
	{
		if (mCurrentAnm->GetNowFrameY() == 5)
		{
			mImage->AlphaScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2, mY - 110, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 200, 130, mAlpha);
		}
		else
			mImage->ScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2, mY - 110, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 200, 130);
	}

	if (mIsDeath != true)
	{
		mHPImage->Render(hdc, mX - 35, mY + 25, 0, 0, 88 * (mHP / mMaxHP), 8);
		mMPImage->Render(hdc, mX - 33, mY + 31, 0, 0, 80 * (mMP / mMaxMP), 8);
		mHPBar->Render(hdc, mX - 36, mY + 25);
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
		if (mCurrentAnm->GetNowFrameY() >= 6)
			mDefImage->Render(hdc, mX - 36, mY + 5);
		else
			mDefImage->Render(hdc, mX + 34, mY + 5);
	}
}