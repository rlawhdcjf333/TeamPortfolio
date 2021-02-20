#include "pch.h"
#include "Staff.h"
#include "Animation.h"

void Staff::Init()
{
	//mImage = IMAGEMANAGER->FindImage();	//랜덤하게 넣기
	mAtk = Random::GetInstance()->RandomInt(20);
	mDef = Random::GetInstance()->RandomInt(20);

	//champ들의 name중에서 랜덤 2개 < champ완성되거나 몇개 만들어지면 넣어야할듯?
	wstring champName = L"챔프이름1";//champ이름 아무거나 뽑아오는 함수? < objectmanager에서 ObjectLayer::Champ인데에서 뽑아오는거 만들기
	mMostChamp.insert(make_pair(champName, 3));
	wstring champName = L"챔프이름2";
	mMostChamp.insert(make_pair(champName, 3));

	mChar1 = (Character)Random::GetInstance()->RandomInt(8);
	mChar2 = (Character)Random::GetInstance()->RandomInt(9);

	mTraningPoint = 0;

	//이미지 작업한 다음에 애니메이션 모션 만들어서 넣기
	/*
	Animation* tempAnm = new Animation();
	tempAnm->InitFrameByStartEnd(min, Y, max, Y, true);
	tempAnm->SetIsLoop(true);
	tempAnm->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", tempAnm));
	mCurrentAnm = tempAnm;
	*/
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
}

void Staff::Render(HDC hdc)
{
	//mImage->FrameRender(hdc, mX, mY, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY());
}
