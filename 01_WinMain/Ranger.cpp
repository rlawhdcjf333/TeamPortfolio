#include "pch.h"
#include "Ranger.h"
#include "Animation.h"

Ranger::Ranger()
	:Champ("Ranger") {}


void Ranger::Init()
{
	//이미지 로드하고 넣기
	IMAGEMANAGER->LoadFromFile(L"Ranger", Resources(L"Ranger.bmp"), 840, 1680, 7, 14,  true);
	mImage= IMAGEMANAGER->FindImage(L"Ranger");

	//변수 초기화
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

	//애니메이션
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
	//각각의 적들의 상태가 엑티브인 애들의 거리를 찾아서 가까운 애가 타겟이 되게 설정한다.
	//우선 엑티브가 트루인지 폴스인지 확인후 트루면 값을 넣어주고 아니면 0을 넣어서 거리값을 비교하게 한다.
	//비교했을 때 거리가 가까운 애를 타겟으로 한다.

	mMP += Time::GetInstance()->DeltaTime();	//MP 1씩 깎아주기
	mSkill1Cool -= Time::GetInstance()->DeltaTime(); //스킬 쿨 돌아가게 해주기
	mAttackCool -= Time::GetInstance()->DeltaTime(); //공격 쿨 돌아가게 해주기

	//{{디스턴스 넣기
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
	//Champ* tmp = (Champ*)mTarget;		//타겟이 확정됐으니 적 체력세팅을 위해 다운캐스팅해버림
	mAngle = Math::GetAngle(mX, mY, mTarget->GetX(), mTarget->GetY());
	//}}

	//{{설정된 타겟이 사거리 안에 들어 온다면 궁극기 > 스킬 > 공격 순으로 행동을 하게한다.
	if (mRange <= mTargetDistance)	//타겟이 사거리 안에 있다.
	{
		if (mX < mTarget->GetX())//타겟이 오른쪽에 있다
		{
			if (mMP >= 100)//마나가	100이상이 있다면
			{
				mCurrentAnm->Stop();
				mCurrentAnm = mAnimationList.find(L"RightSkill2")->second; //스킬2 모션을 실행한다.
				mCurrentAnm->Play();

				if (mCurrentAnm->GetCurrentFrameIndex() == 6)//궁극기 스킬의 끝프레임 까지 갔다면 타겟의 HP를 복합적인 연산으로 깎고 모션을 아이들로 바꾼다.
				{
					Champ* tmp = (Champ*)mTarget;			//타겟을 챔프로 다운캐스팅
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
						Champ* tmp = (Champ*)mTarget;	//타겟을 챔프로 다운캐스팅
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
							Champ* tmp = (Champ*)mTarget;	//타겟을 챔프로 다운캐스팅
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
					Champ* tmp = (Champ*)mTarget;			//타겟을 챔프로 다운캐스팅
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
						Champ* tmp = (Champ*)mTarget;	//타겟을 챔프로 다운캐스팅
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
							Champ* tmp = (Champ*)mTarget;	//타겟을 챔프로 다운캐스팅
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
		//}}
	}
	
	

	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	mCurrentAnm->Update();
}
void Ranger::Render(HDC hdc)
{

}