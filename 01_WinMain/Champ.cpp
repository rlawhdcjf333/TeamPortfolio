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

	//애니메이션
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
	
	Champ* tmp = (Champ*)mTarget;		//타겟이 확정됐으니 적 체력세팅을 위해 다운캐스팅해버림
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

	Champ* tmp = (Champ*)mTarget;		//타겟이 확정됐으니 적 체력세팅을 위해 다운캐스팅해버림
	mAngle = Math::GetAngle(mX, mY, mTarget->GetX(), mTarget->GetY());
	
	if (mHP <= 0)											//죽었을 때 알고리즘 
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
				mHP = mFullHP;				//자 그런데 모든 캐릭터의 HP는 똑같지 않을 터이니 mHP = mCharacterHPMAX라는 예시 변수를 사용해서 받아올 수 있게 만들어보자
			}							//그럼 Init 매개변수에 float CharacterHPMAX라는 것을 선언해줘야 하는데 오버라이드가 되어 사용할 수 없다. 
		}								//어떻게 받아오는게 좋을까? 어제 지원동생이 생성자를 이용해보라고 했었다 이것이 힌트일 것 같다.

	}



	//{{설정된 타겟이 사거리 안에 들어 온다면 궁극기 > 스킬 > 공격 순으로 행동을 하게한다.
	if (mRange <= mTargetDistance)	//타겟이 사거리 안에 있다.
	{
		if (mX < mTarget->GetX())//타겟이 오른쪽에 있다
		{
			if (mMP >= mSkill1Cool)//마나가 이상이 있다면
			{
				mCurrentAnm->Stop();
				mCurrentAnm = mAnimationList.find(L"RightSkill2")->second; //스킬2 모션을 실행한다.
				mCurrentAnm->Play();

				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//궁극기 스킬의 끝프레임 까지 갔다면 타겟의 HP를 복합적인 연산으로 깎고 모션을 아이들로 바꾼다.
				{
					tmp->SetHP(tmp->GetHP() - 100);			//HP를 깎는다.
					mMP = 0;								//마나를 0으로 초기화
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//모션을 아이들로 한다.
					mCurrentAnm->Play();
				}
			}
			else
			{
				if (mSkill1Cool <= 0)	//마나가 없고 스킬쿨이 0보다 아래라면
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"RightSkill1")->second;//스킬1 모션을 실행한다.
					mCurrentAnm->Play();

					if (mCurrentAnm->GetCurrentFrameIndex() == 6)//스킬1의 끝 프레임 까지 갔다면 타겟의 HP를 복합적인 연산 후 깎고 모션을 아이들로 바꾼다.
					{
						tmp->SetHP(tmp->GetHP() - 100);	//HP를 깎는다.
						mSkill1Cool = 5;				//쿨타임을 원래대로 초기화
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//모션을 아이들로 한다.
						mCurrentAnm->Play();
					}
				}
				else
				{
					if (mAttackCool <= 0)	//마나가 없고 스킬쿨이 0보다 아래가 아니고 공격쿨이 0보다 아래라면
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"RightAttack")->second;//공격 모션을 실행한다.
						mCurrentAnm->Play();

						if (mCurrentAnm->GetCurrentFrameIndex() == 6)//스킬1의 끝 프레임 까지 갔다면 타겟의 HP를 복합적인 연산 후 깎고 모션을 아이들로 바꾼다.
						{
							tmp->SetHP(tmp->GetHP() - 100);	//HP를 깎는다.
							mAttackCool = 5;				//쿨타임을 원래대로 초기화
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//모션을 아이들로 한다.
							mCurrentAnm->Play();
						}
					}
					else	//마나가 없고 스킬쿨이 0보다 아래가 아니고 공격쿨이 0보다 아래가 아니라면 아이들 상태로 바꾸자
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;
						mCurrentAnm->Play();
					}
				}
			}
		}

		else if (mX > mTarget->GetX())	//타겟이 왼쪽에 있다면
		{
			if (mMP >= 100)//마나가	100이상이 있다면
			{
				mCurrentAnm->Stop();
				mCurrentAnm = mAnimationList.find(L"LeftSkill2")->second; //스킬2 모션을 실행한다.
				mCurrentAnm->Play();

				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//궁극기 스킬의 끝프레임 까지 갔다면 타겟의 HP를 복합적인 연산으로 깎고 모션을 아이들로 바꾼다.
				{
					tmp->SetHP(tmp->GetHP() - 100);			//HP를 깎는다.
					mMP = 0;								//마나를 0으로 초기화
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//모션을 아이들로 한다.
					mCurrentAnm->Play();
				}
			}
			else
			{
				if (mSkill1Cool <= 0)	//마나가 없고 스킬쿨이 0보다 아래라면
				{
					mCurrentAnm->Stop();
					mCurrentAnm = mAnimationList.find(L"LeftSkill1")->second;//스킬1 모션을 실행한다.
					mCurrentAnm->Play();

					if (mCurrentAnm->GetCurrentFrameIndex() == 6)//스킬1의 끝 프레임 까지 갔다면 타겟의 HP를 복합적인 연산 후 깎고 모션을 아이들로 바꾼다.
					{
						tmp->SetHP(tmp->GetHP() - 100);	//HP를 깎는다.
						mSkill1Cool = 5;				//쿨타임을 원래대로 초기화
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftIdle")->second;	//모션을 아이들로 한다.
						mCurrentAnm->Play();
					}
				}
				else
				{
					if (mAttackCool <= 0)	//마나가 없고 스킬쿨이 0보다 아래가 아니고 공격쿨이 0보다 아래라면
					{
						mCurrentAnm->Stop();
						mCurrentAnm = mAnimationList.find(L"LeftAttack")->second;//공격 모션을 실행한다.
						mCurrentAnm->Play();

						if (mCurrentAnm->GetCurrentFrameIndex() == 6)//스킬1의 끝 프레임 까지 갔다면 타겟의 HP를 복합적인 연산 후 깎고 모션을 아이들로 바꾼다.
						{
							tmp->SetHP(tmp->GetHP() - 100);	//HP를 깎는다.
							mAttackCool = 5;				//쿨타임을 원래대로 초기화
							mCurrentAnm->Stop();
							mCurrentAnm = mAnimationList.find(L"RightIdle")->second;	//모션을 아이들로 한다.
							mCurrentAnm->Play();
						}
					}
					else	//마나가 없고 스킬쿨이 0보다 아래가 아니고 공격쿨이 0보다 아래가 아니라면 아이들 상태로 바꾸자
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

	else//{{사거리 안에 타겟이 없다면
	{
		if (mX < mTarget->GetX())	//타겟이 오른쪽에 있다면
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"RightRun")->second;	//모션을 오른쪽 런으로 한다.
			mCurrentAnm->Play();

		}
		else if (mX > mTarget->GetX())	//타겟이 왼쪽에 있다면
		{
			mCurrentAnm->Stop();
			mCurrentAnm = mAnimationList.find(L"LeftRun")->second;	//모션을 왼쪽 런으로 한다.
			mCurrentAnm->Play();
		}

		mX += cosf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;	//이동속도만큼 X,Y값에 값을 더한다.
		mY -= sinf(mAngle)*Time::GetInstance()->DeltaTime()*mSpeed;
	}

	//마나 얻는 알고리즘
	mMPSecGet += Time::GetInstance()->DeltaTime();
	if (mMPSecGet >= 5)
	{
		mMPSecGet = 0;
		mMP += 20;
	}

	//mPlayerList가 있고 mEnemyList

	// 공격을 하였을 시 마나 N개를 얻게 하는 알고리즘
	//if(Range범위 안에 mEnemyList가 들어왔을 경우.)
	//AtkCool -= Time::GetInstance()->DeltaTime();			//Ex) AtkCool = 1.23f다.
	//if(AtkCool <= 0)
	//mMP += N;
	//mHP -= mAtk					//다만 누구껏의 mHP고 mAtk인지 명시해줘야 할 것이다. (플레이어 것인가 적의 것인가)
	//AtkCool = 1.23f				//단 여기에 있는 숫자도, 각 챔프들마다 공격속도가 다를 터이니 매개변수로 받을 수 있게 해줘야할것 같다.

	//원거리 알고리즘
	
	


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
