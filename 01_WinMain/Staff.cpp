#include "pch.h"
#include "Staff.h"
#include "Animation.h"

Staff::Staff(const string& name, const string& staffName, const wstring& teamName)
	:GameObject(name)
{
	mIsActive = false;
	mStaffName = staffName;
	mTeamName = teamName;
	mFileName = L"Staff";
}

void Staff::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;

	mAtk = Random::GetInstance()->RandomInt(3, 7);
	mDef = Random::GetInstance()->RandomInt(3, 7);

	//champ들의 name중에서 랜덤 2개 < champ완성되거나 몇개 만들어지면 넣어야할듯?, 자료형 나중에 맞추지 뭐
	string champName = "챔프이름1";//champ이름 아무거나 뽑아오는 함수? < objectmanager에서 ObjectLayer::Champ인데에서 뽑아오는거 만들기, 
	mMostChamp.insert(make_pair(champName, 3));
	string champName2 = "챔프이름2";
	mMostChamp.insert(make_pair(champName2, 3));

	mChar1 = (Character)Random::GetInstance()->RandomInt(8);
	mChar2 = (Character)Random::GetInstance()->RandomInt(9);

	mTraningPoint = 0;

	mRandomIndexX = Random::GetInstance()->RandomInt(10);
	mRandomIndexY = Random::GetInstance()->RandomInt(8);

	mCondition = (Condition)Random::GetInstance()->RandomInt(1, 4);
	
	IMAGEMANAGER->LoadFromFile(L"Condition", Resources(L"Condition.bmp"), 150, 30, 5, 1, true);
	mConditionImage = IMAGEMANAGER->FindImage(L"Condition");
	SetConditionImage();

	IMAGEMANAGER->LoadFromFile(mFileName, Resources(mFileName + L".bmp"), 960, 512, 30, 16, true);
	mImage = IMAGEMANAGER->FindImage(mFileName);

	mRenderSizeX = mImage->GetFrameWidth() * 2;
	mRenderSizeY = mImage->GetFrameHeight() * 2;

	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2, mRandomIndexX * 3, mRandomIndexY * 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2 + 1, mRandomIndexX * 3, mRandomIndexY * 2 + 1, true);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2, mRandomIndexX * 3 + 2, mRandomIndexY * 2, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2 + 1, mRandomIndexX * 3 + 2, mRandomIndexY * 2 + 1, true);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));
}

void Staff::Release()
{
	map<wstring, Animation*> :: iterator iter = mAnimationList.begin();
	for (; iter != mAnimationList.end(); ++iter) {
		SafeDelete(iter->second);
	}
}

void Staff::Update()
{
	//??뭘 업데이트 해야하지?
	if (mIsActive)
	{
		SetConditionImage();
		mCurrentAnm->Update();
	}
}

void Staff::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->ScaleFrameRender(hdc, mX, mY, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), mRenderSizeX, mRenderSizeY);
	}
}

void Staff::UIRender(HDC hdc, int startX, int startY, int width, int height)
{
	mImage->ScaleFrameRender(hdc, startX, startY, mRandomIndexX*3, mRandomIndexY*2, width, height);
}

void Staff::ConditionRender(HDC hdc, int startX, int startY, int width, int height)
{
	mConditionImage->ScaleFrameRender(hdc, startX, startY, mConditionX, 0, width, height);
}

void Staff::SetConditionImage()
{
	switch (mCondition)
	{
	case Condition::Bad:
		mConditionX = 0;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::LittleBad:
		mConditionX = 1;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::Nomal:
		mConditionX = 2;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::Good:
		mConditionX = 3;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::Best:
		mConditionX = 4;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	}
}
