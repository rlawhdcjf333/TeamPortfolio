#include "pch.h"
#include "Staff.h"
#include "Animation.h"

void Staff::Init()
{
	//mImage = IMAGEMANAGER->FindImage();	//�����ϰ� �ֱ�
	mAtk = Random::GetInstance()->RandomInt(20);
	mDef = Random::GetInstance()->RandomInt(20);

	//champ���� name�߿��� ���� 2�� < champ�ϼ��ǰų� � ��������� �־���ҵ�?
	wstring champName = L"è���̸�1";//champ�̸� �ƹ��ų� �̾ƿ��� �Լ�? < objectmanager���� ObjectLayer::Champ�ε����� �̾ƿ��°� �����
	mMostChamp.insert(make_pair(champName, 3));
	wstring champName = L"è���̸�2";
	mMostChamp.insert(make_pair(champName, 3));

	mChar1 = (Character)Random::GetInstance()->RandomInt(8);
	mChar2 = (Character)Random::GetInstance()->RandomInt(9);

	mTraningPoint = 0;

	//�̹��� �۾��� ������ �ִϸ��̼� ��� ���� �ֱ�
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
	//??�� ������Ʈ �ؾ�����?
}

void Staff::Render(HDC hdc)
{
	//mImage->FrameRender(hdc, mX, mY, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY());
}
