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

<<<<<<< Updated upstream
	mCondition = (Condition)Random::GetInstance()->RandomInt(1, 4);
	
	IMAGEMANAGER->LoadFromFile(L"Condition", Resources(L"Condition.bmp"), 150, 30, 5, 1, true);
=======
	mCondition = (Condition)Random::GetInstance()->RandomInt(4);
	//컨디션 이미지 작업하면 아래 세 줄 주석 제거
	IMAGEMANAGER->LoadFromFile(L"Condition", Resources(L"Condition"), 150, 30, 5, 1, true);
>>>>>>> Stashed changes
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

wstring Staff::GetCharComment(int Charnum)
{
	wstring comment = L" ";
	Character ch;
	if (Charnum == 1)
		ch = mChar1;
	else if (Charnum == 2)
		ch = mChar2;
	else
		return comment;	//다른인덱스 넣으면 공백

	switch (ch)
	{
	case Character::Nomal:
		comment = L"평범";	// 아무 특성 없음
		break;
	case Character::Hero:	//영웅 : 이기고 있을때 모든 능력치 -10, 지고 있을때 +10
		comment = L"영웅";
		break;
	case Character::Glass:	//유리멘탈 : 이기고 있을때 모든 능력치 +10, 지고 있을때 -10
		comment = L"유리";
		break;
	case Character::Mother:	//엄마 : 회복력 + 10
		comment = L"엄마";
		break;
	case Character::Thorn:	//가시 : 상대방의 회복력 -10
		comment = L"가시";
		break;
	case Character::Winner:	//승리자 : 처치관여(assist)시 체력 +10
		comment = L"승자";
		break;
	case Character::Distraction://주의산만 : 공격대상이 5초마다 무작위로 변경
		comment = L"산만";
		break;
	case Character::Fest:	//쾌속 : 스킬 시전속도 10% 증가
		comment = L"쾌속";
		break;
	case Character::Spear:	//꿰뚫는 창 : 방어력 관통효과 +10(상대방의 방어력을 10 무시한다)
		comment = L"죽창";
		break;
	case Character::None:	//비어있는 특성(표시 안하는 상태)
		break;
	default:
		break;
	}
	return comment;
}

void Staff::SetConditionImage()
{
	switch (mCondition)
	{
	case Condition::Bad:
		mConditionX = 4;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::LittleBad:
		mConditionX = 3;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::Nomal:
		mConditionX = 2;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::Good:
		mConditionX = 1;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	case Condition::Best:
		mConditionX = 0;	//임시로 넣은 인덱스, 이미지보고 조정
		break;
	}
}
