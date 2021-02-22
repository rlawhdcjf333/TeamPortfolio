#include "pch.h"
#include "Staff.h"
#include "Animation.h"

Staff::Staff(const string& name)
	:GameObject(name)
{
	mFileName = L"Staff";
}

Staff::Staff(const string& name, const wstring& fileName)
	:GameObject(name)
{
	mFileName = fileName;
	mIsActive = false;
}

void Staff::Init()
{

	mAtk = Random::GetInstance()->RandomInt(3, 7);
	mDef = Random::GetInstance()->RandomInt(3, 7);

	//champ���� name�߿��� ���� 2�� < champ�ϼ��ǰų� � ��������� �־���ҵ�?, �ڷ��� ���߿� ������ ��
	wstring champName = L"è���̸�1";//champ�̸� �ƹ��ų� �̾ƿ��� �Լ�? < objectmanager���� ObjectLayer::Champ�ε����� �̾ƿ��°� �����, 
	mMostChamp.insert(make_pair(champName, 3));
	wstring champName2 = L"è���̸�2";
	mMostChamp.insert(make_pair(champName2, 3));

	mChar1 = (Character)Random::GetInstance()->RandomInt(8);
	mChar2 = (Character)Random::GetInstance()->RandomInt(9);

	mTraningPoint = 0;

	mRandomIndexX = Random::GetInstance()->RandomInt(10);
	mRandomIndexY = Random::GetInstance()->RandomInt(8);

	IMAGEMANAGER->LoadFromFile(mFileName, Resources(mFileName + L".bmp"), 960, 512, 30, 16, true);
	mImage = IMAGEMANAGER->FindImage(mFileName);

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
	//??�� ������Ʈ �ؾ�����?
	mCurrentAnm->Update();
}

void Staff::Render(HDC hdc)
{
	if (mIsActive) {
		mImage->ScaleFrameRender(hdc, mX, mY, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), mImage->GetFrameWidth() * 2, mImage->GetFrameHeight() * 2);
	}
}