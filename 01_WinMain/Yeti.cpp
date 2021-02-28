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
	mSkill = 0;									//지역변수 선언 
	mSpecialSkill = 100;

	mChampEx = L"엘나스에서 평화롭게 지내던 설인. 튼튼한 체력과 넉백으로 아군을 지켜준다.";

	//애니메이션
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

				if (mCurrentAnm->GetCurrentFrameIndex() == 9)//궁극기 스킬의 끝프레임 까지 갔다면 타겟의 HP를 복합적인 연산으로 깎고 모션을 아이들로 바꾼다.
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

void Yeti::Render(HDC hdc)
{
}
