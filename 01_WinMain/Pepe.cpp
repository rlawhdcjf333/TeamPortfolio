#include "pch.h"
#include "Pepe.h"
#include "Animation.h"
#include "Image.h"

Pepe::Pepe()
	:Champ("Pepe") {}

Pepe::Pepe(string str, float x, float y)
	: Champ(str)
{
	mX = x;
	mY = y;
	mRespawnX = x;
	mRespawnY = y;
}

Pepe::Pepe(const string& name) 
	:Champ(name)
{
	mChampName = L"Pepe";
	mClassType = ClassType::Warrior;
}

void Pepe::Init()
{
	//is action 이 트루면 다른 행동 못하게 해야됨
	//이미지 로드하고 넣기
	IMAGEMANAGER->LoadFromFile(L"Pepe", Resources(L"Pepe.bmp"), 1040, 1440, 8, 12, true);
	IMAGEMANAGER->LoadFromFile(L"HPBar", Resources(L"hpmpbar.bmp"), 90, 15, true);
	IMAGEMANAGER->LoadFromFile(L"HP", Resources(L"hp.bmp"), 88, 8, true);
	IMAGEMANAGER->LoadFromFile(L"MP", Resources(L"mp.bmp"), 80, 8, true);
	IMAGEMANAGER->LoadFromFile(L"exclamation", Resources(L"exclamation.bmp"), 40, 40, true);
	IMAGEMANAGER->LoadFromFile(L"Def", Resources(L"Def.bmp"), 20, 20, true);
	IMAGEMANAGER->LoadFromFile(L"PepeSkill", Resources(L"SkillIcon/PepeSkill.bmp"), 62, 62, true);
	IMAGEMANAGER->LoadFromFile(L"PepeSpecialSkill", Resources(L"SkillIcon/PepeSpecialSkill.bmp"), 62, 62, true);

	mImage = IMAGEMANAGER->FindImage(L"Pepe");
	mHPBar = IMAGEMANAGER->FindImage(L"HPBar");
	mHPImage = IMAGEMANAGER->FindImage(L"HP");
	mMPImage = IMAGEMANAGER->FindImage(L"MP");
	mExclamation = IMAGEMANAGER->FindImage(L"exclamation");
	mDefImage = IMAGEMANAGER->FindImage(L"Def");
	mSkillImage = IMAGEMANAGER->FindImage(L"PepeSkill");
	mSpecialSkillImage = IMAGEMANAGER->FindImage(L"PepeSpecialSkill");

	mChampEx = L"헬멧을 뒤집어 쓴 펭귄. 이유는 모르겠지만 도발적이다.";
	mSkillEx = L"자신 주변의 상대를 3초간 도발한다.";
	mSpecialSkillEx = L"남극지방 전통춤을 추어 모든 아군의 방어력을 일정시간 올린다.";

	//변수 초기화
	mMaxHP = 150;
	mMaxMP = 100;
	mHP = mMaxHP;
	mMP = 0;
	mInitAtk = 15;
	mAtk = mInitAtk;
	mInitDef = 30;
	mDef = mInitDef;
	mSpeed = 150;
	mRange = 60;
	mMaxAttackCool = 1.5;
	mAttackCool = 0;
	mMaxSkill1Cool = 7;
	mSkill1Cool = mMaxSkill1Cool;
	mDeathCool = 3;
	mAlpha = 0.6;

	mDistance1 = 0;
	mDistance2 = 0;
	mDistance3 = 0;


	mAngle = 0;
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	//애니메이션
	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(0, 6, 5, 6, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;
	mCurrentAnm->Play();

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(0, 7, 7, 7, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* RightAttack = new Animation();
	RightAttack->InitFrameByStartEnd(0, 8, 5, 8, true);
	RightAttack->SetIsLoop(true);
	RightAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightAttack", RightAttack));

	Animation* RightSkill1 = new Animation();
	RightSkill1->InitFrameByStartEnd(0, 9, 4, 9, true);
	RightSkill1->SetIsLoop(true);
	RightSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill1", RightSkill1));

	Animation* RightSkill2 = new Animation();
	RightSkill2->InitFrameByStartEnd(0, 10, 7, 10, true);
	RightSkill2->SetIsLoop(true);
	RightSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightSkill2", RightSkill2));

	Animation* RightDeath = new Animation();
	RightDeath->InitFrameByStartEnd(0, 11, 7, 11, true);
	RightDeath->SetIsLoop(true);
	RightDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightDeath", RightDeath));

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(0, 0, 5, 0, false);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(0, 1, 7, 1, false);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.1f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));

	Animation* LeftAttack = new Animation();
	LeftAttack->InitFrameByStartEnd(0, 2, 5, 2, false);
	LeftAttack->SetIsLoop(true);
	LeftAttack->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftAttack", LeftAttack));

	Animation* LeftSkill1 = new Animation();
	LeftSkill1->InitFrameByStartEnd(0, 3, 4, 3, false);
	LeftSkill1->SetIsLoop(true);
	LeftSkill1->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill1", LeftSkill1));

	Animation* LeftSkill2 = new Animation();
	LeftSkill2->InitFrameByStartEnd(0, 4, 7, 4, false);
	LeftSkill2->SetIsLoop(true);
	LeftSkill2->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftSkill2", LeftSkill2));

	Animation* LeftDeath = new Animation();
	LeftDeath->InitFrameByStartEnd(0, 5, 7, 5, false);
	LeftDeath->SetIsLoop(true);
	LeftDeath->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftDeath", LeftDeath));

	mapIter = mAnimationList.begin();
}

void Pepe::Release()
{

}
void Pepe::Update()
{
	Champ::Update();
	if (mIsDeath == true && mDeathCool <= 0)
	{
		mX = mRespawnX;	//부활했을 때 리스폰 장소로 초기화 해주자
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

	//각각의 적들의 상태가 엑티브인 애들의 거리를 찾아서 가까운 애가 타겟이 되게 설정한다.
	//우선 엑티브가 트루인지 폴스인지 확인후 트루면 값을 넣어주고 아니면 0을 넣어서 거리값을 비교하게 한다.
	//비교했을 때 거리가 가까운 애를 타겟으로 한다.
	if (mCurrentAnm != mAnimationList.find(L"RightSkill2")->second && mCurrentAnm != mAnimationList.find(L"LeftSkill2")->second)
		mMP += Time::GetInstance()->DeltaTime() * 7;	//MP 1씩 더해주기
	if (mCurrentAnm != mAnimationList.find(L"RightSkill1")->second && mCurrentAnm != mAnimationList.find(L"LeftSkill1")->second)
		mSkill1Cool -= Time::GetInstance()->DeltaTime(); //스킬 쿨 돌아가게 해주기
	if (mCurrentAnm != mAnimationList.find(L"RightAttack")->second && mCurrentAnm != mAnimationList.find(L"LeftAttack")->second)
		mAttackCool -= Time::GetInstance()->DeltaTime(); //공격 쿨 돌아가게 해주기

	if (mEnemyList.size() <= 0)
	{
		if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
		{
			mCurrentAnm->Stop();
			mapIter++;
			if (mapIter == mAnimationList.end())			//이미지 괜찮은지 보는 기능
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
	//{{적 세팅하기 (디스턴스 + 타겟잡기)
	vector<Champ*>temp;
	for (int i = 0; i < 3; i++)
	{
		Champ* tmp = (Champ*)mEnemyList[i];			//다운캐스팅해서 isdeath로 죽었는지 확인 
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


	Champ* tmp = (Champ*)mTarget;		//타겟이 확정됐으니 적 체력세팅을 위해 다운캐스팅해버림
	mAngle = Math::GetAngle(mX, mY, mTarget->GetX(), mTarget->GetY());
	//}}


	//{{설정된 타겟이 사거리 안에 들어 온다면 궁극기 > 스킬 > 공격 순으로 행동을 하게한다.
	if (!(temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true)) //모두 살아있을 때만 작동
	{
		if (mRange >= mTargetDistance && mIsAction == false)	//타겟이 사거리 안에 있다.
		{
			if (mX < mTarget->GetX())//타겟이 오른쪽에 있다
			{
				if (mMP >= 100)//마나가	100이상이 있다면
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightSkill2")->second; //스킬2 모션을 실행한다.
					mCurrentAnm->Play();
					mIsAction = true;	//액션을 트루로 바꾼다.

				}
				else
				{
					if (mSkill1Cool <= 0)	//마나가 없고 스킬쿨이 0보다 아래라면
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightSkill1")->second;//스킬1 모션을 실행한다.
						mCurrentAnm->Play();
						mIsAction = true;	//액션을 트루로 바꾼다.
					}
					else
					{
						if (mAttackCool <= 0)	//마나가 없고 스킬쿨이 0보다 아래가 아니고 공격쿨이 0보다 아래라면
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightAttack")->second;//공격 모션을 실행한다.
							mCurrentAnm->Play();
							mIsAction = true;	//액션을 트루로 바꾼다.
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

			else if (mX > mTarget->GetX() && mIsAction == false)	//타겟이 왼쪽에 있다면
			{
				if (mMP >= 100)//마나가	100이상이 있다면
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftSkill2")->second; //스킬2 모션을 실행한다.
					mCurrentAnm->Play();
					mIsAction = true;	//액션을 트루로 바꾼다.
				}
				else
				{
					if (mSkill1Cool <= 0)	//마나가 없고 스킬쿨이 0보다 아래라면
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftSkill1")->second;//스킬1 모션을 실행한다.
						mCurrentAnm->Play();
						mIsAction = true;	//액션을 트루로 바꾼다.
					}
					else
					{
						if (mAttackCool <= 0)	//마나가 없고 스킬쿨이 0보다 아래가 아니고 공격쿨이 0보다 아래라면
						{
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftAttack")->second;//공격 모션을 실행한다.
							mCurrentAnm->Play();
							mIsAction = true;	//액션을 트루로 바꾼다.
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
		else if (mRange < mTargetDistance && mIsAction == false)//{{사거리 안에 타겟이 없다면
		{
			if (mX <= mTarget->GetX())	//타겟이 오른쪽에 있다면
			{
				if (mCurrentAnm != mAnimationList.find(L"RightRun")->second)
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightRun")->second;	//모션을 오른쪽 런으로 한다.
					mCurrentAnm->Play();
				}
			}
			else if (mX > mTarget->GetX())	//타겟이 왼쪽에 있다면
			{
				if (mCurrentAnm != mAnimationList.find(L"LeftRun")->second)
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftRun")->second;	//모션을 왼쪽 런으로 한다.
					mCurrentAnm->Play();
				}
			}


			if (!(temp[0]->GetIsDeath() == true && temp[1]->GetIsDeath() == true && temp[2]->GetIsDeath() == true))	//모두 죽었을 때 안 움직이게 한다.
			{
				mX += cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;	//이동속도만큼 X,Y값에 값을 더한다.
				mY -= sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
			}
			mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
		}


		//{{어떤 모션을 취했을 시
		if (mIsAction == true)
		{
			if (mCurrentAnm == mAnimationList.find(L"RightSkill2")->second && mCurrentAnm->GetCurrentFrameIndex() == 7
				|| mCurrentAnm == mAnimationList.find(L"LeftSkill2")->second && mCurrentAnm->GetCurrentFrameIndex() == 7)
			{
				mMP = 0;
				DefBuff(15, 5);
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 4
				|| mCurrentAnm == mAnimationList.find(L"LeftSkill1")->second && mCurrentAnm->GetCurrentFrameIndex() == 4)
			{
				//HP를 까던지 어떤 걸 행한 후에 이즈액션 폴스로
				Aggro(3);
				mSkill1Cool = mMaxSkill1Cool;
				mIsAction = false;
			}
			if ((mCurrentAnm == mAnimationList.find(L"RightAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 5)
				|| (mCurrentAnm == mAnimationList.find(L"LeftAttack")->second && mCurrentAnm->GetCurrentFrameIndex() == 5))
			{
				//HP를 까던지 어떤 걸 행한 후에 이즈액션 폴스로
				tmp->SetHP(tmp->GetHP() - (mAtk *(1 - (tmp->GetDef() / (tmp->GetDef() + 30)))));
				mAttackCool = mMaxAttackCool;
				mIsAction = false;
			}
			if (mCurrentAnm == mAnimationList.find(L"RightIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 5
				|| mCurrentAnm == mAnimationList.find(L"LeftIdle")->second && mCurrentAnm->GetCurrentFrameIndex() == 5)
			{
				//HP를 까던지 어떤 걸 행한 후에 이즈액션 폴스로
				mIsAction = false;
			}
		}
	}
	//}}

	//적이 모두 죽어있을 때 아이들 상태로 만든다.
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

	//}}보정
	//경기장 밖으로 가면 보정해주자
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
void Pepe::Render(HDC hdc)
{
	//RenderRect(hdc, mRect);
	//Rectangle(hdc,mX - 100, mY - 100, mX + 100, mY + 100);
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
			mImage->AlphaScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2 + 42, mY - 60, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 80, 70, mAlpha);
		}
		else
			mImage->ScaleFrameRender(hdc, mX - mImage->GetFrameWidth() / 2 + 42, mY - 60, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 80, 70);
	}


	if (mIsDeath != true)
	{
		mHPImage->Render(hdc, mX - 35, mY + 10, 0, 0, 88 * (mHP / mMaxHP), 8);
		mMPImage->Render(hdc, mX - 33, mY + 16, 0, 0, 80 * (mMP / mMaxMP), 8);
		mHPBar->Render(hdc, mX - 36, mY + 10);
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
			mDefImage->Render(hdc, mX - 36, mY - 10);
		else
			mDefImage->Render(hdc, mX + 34, mY - 10);
	}
}