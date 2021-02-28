#include "pch.h"
#include "LoveMonkey.h"
#include "Animation.h"
#include "Image.h"

LoveMonkey::LoveMonkey()
	:Champ("LoveMonkey") {}

LoveMonkey::LoveMonkey(const string& name)
	: Champ(name)
{
	mChampName = L"LoveMonkey";
	mClassType = ClassType::Supporter;
}

LoveMonkey::LoveMonkey(string str, float x, float y)
	: Champ(str)
{
	mX = x;
	mY = y;
	mRespawnX = x;
	mRespawnY = y;
}

void LoveMonkey::Init()
{
	//is action �� Ʈ��� �ٸ� �ൿ ���ϰ� �ؾߵ�
	//�̹��� �ε��ϰ� �ֱ�
	IMAGEMANAGER->LoadFromFile(L"LoveMonkey", Resources(L"LoveMonkey.bmp"), 480, 600, 6, 10, true);
	IMAGEMANAGER->LoadFromFile(L"HPBar", Resources(L"hpmpbar.bmp"), 90, 15, true);
	IMAGEMANAGER->LoadFromFile(L"HP", Resources(L"hp.bmp"), 88, 8, true);
	IMAGEMANAGER->LoadFromFile(L"MP", Resources(L"mp.bmp"), 80, 8, true);
	IMAGEMANAGER->LoadFromFile(L"exclamation", Resources(L"exclamation.bmp"), 40, 40, true);
	IMAGEMANAGER->LoadFromFile(L"Def", Resources(L"Def.bmp"), 20, 20, true);
	IMAGEMANAGER->LoadFromFile(L"MonkeySkill", Resources(L"SkillIcon/MonkeySkill.bmp"), 62, 62, true);
	IMAGEMANAGER->LoadFromFile(L"MonkeySpecialSkill", Resources(L"SkillIcon/MonkeySpecialSkill.bmp"), 62, 62, true);

	mChampEx = L"ť��Ʈ�� �ǰ� ���� �Ʊ� ������. �Ʊ��� ġ���ϴµ� �����̴�.";
	mSkillEx = L"����� ������ �ֺ� ���� ������ �Ʊ��� ȸ����Ų��.";
	mSpecialSkillEx = L"������ ����� ������ �ֺ� ���� ������ �Ʊ��� 3�� ȸ����Ų��.";

	mImage = IMAGEMANAGER->FindImage(L"LoveMonkey");
	mHPBar = IMAGEMANAGER->FindImage(L"HPBar");
	mHPImage = IMAGEMANAGER->FindImage(L"HP");
	mMPImage = IMAGEMANAGER->FindImage(L"MP");
	mExclamation = IMAGEMANAGER->FindImage(L"exclamation");
	mDefImage = IMAGEMANAGER->FindImage(L"Def");
	mSkillImage = IMAGEMANAGER->FindImage(L"MonkeySkill");
	mSpecialSkillImage = IMAGEMANAGER->FindImage(L"MonkeySpecialSkill");
	//���� �ʱ�ȭ
	mMaxHP = 150;
	mMaxMP = 100;
	mHP = 150;
	mMP = 0;
	mInitAtk = 15;
	mAtk = 10;
	mInitDef = 15;
	mDef = 15;
	mInitHealPr = 10;
	mHealPr = 10;
	mSpeed = 175;
	mRange = 60;
	mMaxAttackCool = 2;
	mAttackCool = 0;
	mMaxSkill1Cool = 4;
	mSkill1Cool = 4;
	mDeathCool = 3;
	mAlpha = 0.6;

	mDistance1 = 0;
	mDistance2 = 0;
	mDistance3 = 0;


	mAngle = 0;

	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	//�ִϸ��̼�
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 6, 1, 6, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.9f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 7, 2, 7, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* RightAttack = new Animation();
	RightAttack->InitFrameByStartEnd(0, 8, 1, 8, true);
	RightAttack->SetIsLoop(true);
	RightAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 9, 5, 9, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 10, 5, 10, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 11, 3, 11, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 1, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.9f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 1, 2, 1, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* LeftAttack = new Animation();
	LeftAttack->InitFrameByStartEnd(0, 2, 1, 2, false);
	LeftAttack->SetIsLoop(true);
	LeftAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 3, 5, 3, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 4, 5, 4, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 5, 3, 5, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));

	mapIter = mAnimationList.begin();
}

void LoveMonkey::Release()
{

}
void LoveMonkey::Update()
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
		if (mCurrentAnm->GetCurrentFrameIndex() != 3)
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
	vector<Champ*>temp2;
	for (int i = 0; i < 3; i++)
	{
		Champ* tmp2 = (Champ*)mFriendList[i];			//�ٿ�ĳ�����ؼ� isdeath�� �׾����� Ȯ�� 
		temp2.push_back(tmp2);
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
			if (mCurrentAnm == mAnimationList.find(L"RightSkill2")->second && mCurrentAnm->GetCurrentFrameIndex() >= 3
				|| mCurrentAnm == mAnimationList.find(L"LeftSkill2")->second && mCurrentAnm->GetCurrentFrameIndex() >= 3)
			{
				mMP = 0;
				POINT pt = { temp2[0]->GetX(), temp2[0]->GetY() };
				POINT pt1 = { temp2[1]->GetX(), temp2[1]->GetY() };		//���� Ÿ���� ���� ����Ʈ ����
				POINT pt2 = { temp2[2]->GetX(), temp2[2]->GetY() };
				RECT rc = { mX - 100,mY - 100,mX + 100,mY + 100 };		//���� ��Ʈ ����

				if (PtInRect(&rc, pt))
				{
					temp2[0]->SetHP(temp2[0]->GetHP() + mHealPr * 3 * Time::GetInstance()->DeltaTime());
				}
				if (PtInRect(&rc, pt1))
				{
					temp2[1]->SetHP(temp2[1]->GetHP() + mHealPr * 3 * Time::GetInstance()->DeltaTime());
				}
				if (PtInRect(&rc, pt2))
				{
					temp2[2]->SetHP(temp2[2]->GetHP() + mHealPr * 3 * Time::GetInstance()->DeltaTime());
				}
				if (mCurrentAnm->GetCurrentFrameIndex() == 5)
					mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 5
				|| mCurrentAnm == mAnimationList.find(L"LeftSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 5)
			{

				mSkill1Cool = mMaxSkill1Cool;
				POINT pt = { temp2[0]->GetX(), temp2[0]->GetY() };
				POINT pt1 = { temp2[1]->GetX(), temp2[1]->GetY() };		//���� Ÿ���� ���� ����Ʈ ����
				POINT pt2 = { temp2[2]->GetX(), temp2[2]->GetY() };
				RECT rc = { mX - 100,mY - 100,mX + 100,mY + 100 };		//���� ��Ʈ ����

				if (PtInRect(&rc, pt))
				{
					temp2[0]->SetHP(temp2[0]->GetHP() + mHealPr / 2);
				}
				if (PtInRect(&rc, pt1))
				{
					temp2[1]->SetHP(temp2[1]->GetHP() + mHealPr / 2);
				}
				if (PtInRect(&rc, pt2))
				{
					temp2[2]->SetHP(temp2[2]->GetHP() + mHealPr / 2);
				}
				mIsAction = false;
			}
			if ((mCurrentAnm == mAnimationList.find(L"RightAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 1)
				|| (mCurrentAnm == mAnimationList.find(L"LeftAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 1))
			{
				tmp->SetHP(tmp->GetHP() - (mAtk *(1 - (tmp->GetDef() / (tmp->GetDef() + 30)))));
				mAttackCool = mMaxAttackCool;
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
void LoveMonkey::Render(HDC hdc)
{
	//RenderRect(hdc, mRect);
	if (mCurrentAnm->GetNowFrameY() >= 6)
	{
		if (mCurrentAnm->GetNowFrameY() == 11)
		{
			mImage->AlphaScaleFrameRender(hdc, mX - 42, mY - 60, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 80, 70, mAlpha);
		}
		else
			mImage->ScaleFrameRender(hdc, mX - 42, mY - 60, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 80, 70);
	}
	else
	{
		if (mCurrentAnm->GetNowFrameY() == 5)
		{
			mImage->AlphaScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2 + 6, mY - 60, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 80, 70, mAlpha);
		}
		else
			mImage->ScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2 + 6, mY - 60, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 80, 70);
	}

	wstring atkCool = to_wstring(mHP);
	TextOut(hdc, 50, 50, atkCool.c_str(), atkCool.size());
	if (mIsDeath != true)
	{
		mHPImage->Render(hdc, mX - 45, mY + 13, 0, 0, 88 * (mHP / mMaxHP), 8);
		mMPImage->Render(hdc, mX - 43, mY + 19, 0, 0, 80 * (mMP / mMaxMP), 8);
		mHPBar->Render(hdc, mX - 46, mY + 13);
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
			mDefImage->Render(hdc, mX - 46, mY - 7);
		else
			mDefImage->Render(hdc, mX + 24, mY - 7);
	}
}