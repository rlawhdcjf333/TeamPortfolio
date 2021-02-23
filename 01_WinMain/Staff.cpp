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

	//champ���� name�߿��� ���� 2�� < champ�ϼ��ǰų� � ��������� �־���ҵ�?, �ڷ��� ���߿� ������ ��
	string champName = "è���̸�1";//champ�̸� �ƹ��ų� �̾ƿ��� �Լ�? < objectmanager���� ObjectLayer::Champ�ε����� �̾ƿ��°� �����, 
	mMostChamp.insert(make_pair(champName, 3));
	string champName2 = "è���̸�2";
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
	//����� �̹��� �۾��ϸ� �Ʒ� �� �� �ּ� ����
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
	//??�� ������Ʈ �ؾ�����?
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
		return comment;	//�ٸ��ε��� ������ ����

	switch (ch)
	{
	case Character::Nomal:
		comment = L"���";	// �ƹ� Ư�� ����
		break;
	case Character::Hero:	//���� : �̱�� ������ ��� �ɷ�ġ -10, ���� ������ +10
		comment = L"����";
		break;
	case Character::Glass:	//������Ż : �̱�� ������ ��� �ɷ�ġ +10, ���� ������ -10
		comment = L"����";
		break;
	case Character::Mother:	//���� : ȸ���� + 10
		comment = L"����";
		break;
	case Character::Thorn:	//���� : ������ ȸ���� -10
		comment = L"����";
		break;
	case Character::Winner:	//�¸��� : óġ����(assist)�� ü�� +10
		comment = L"����";
		break;
	case Character::Distraction://���ǻ길 : ���ݴ���� 5�ʸ��� �������� ����
		comment = L"�길";
		break;
	case Character::Fest:	//��� : ��ų �����ӵ� 10% ����
		comment = L"���";
		break;
	case Character::Spear:	//��մ� â : ���� ����ȿ�� +10(������ ������ 10 �����Ѵ�)
		comment = L"��â";
		break;
	case Character::None:	//����ִ� Ư��(ǥ�� ���ϴ� ����)
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
		mConditionX = 4;	//�ӽ÷� ���� �ε���, �̹������� ����
		break;
	case Condition::LittleBad:
		mConditionX = 3;	//�ӽ÷� ���� �ε���, �̹������� ����
		break;
	case Condition::Nomal:
		mConditionX = 2;	//�ӽ÷� ���� �ε���, �̹������� ����
		break;
	case Condition::Good:
		mConditionX = 1;	//�ӽ÷� ���� �ε���, �̹������� ����
		break;
	case Condition::Best:
		mConditionX = 0;	//�ӽ÷� ���� �ε���, �̹������� ����
		break;
	}
}
