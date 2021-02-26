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

	mChar1 = (Character)Random::GetInstance()->RandomInt(8);
	mChar2 = (Character)Random::GetInstance()->RandomInt(9);

	mTrainingPoint = 3;

	mRandomIndexX = Random::GetInstance()->RandomInt(10);
	mRandomIndexY = Random::GetInstance()->RandomInt(8);

	string rand1 = "Champ" + to_string(Random::GetInstance()->RandomInt(1, 9));
	string rand2 = "Champ" + to_string(Random::GetInstance()->RandomInt(1, 9));

	while (rand1 == rand2)
	{
		rand2 = "Champ" + to_string(Random::GetInstance()->RandomInt(1, 9));
	}

	mMostChamp.insert(make_pair(rand1, Random::GetInstance()->RandomInt(1, 4)));
	mMostChamp.insert(make_pair(rand2, Random::GetInstance()->RandomInt(1, 4)));

	mCondition = (Condition)Random::GetInstance()->RandomInt(4);

	IMAGEMANAGER->LoadFromFile(L"Condition", Resources(L"Condition.bmp"), 150, 30, 5, 1, true);
	mConditionImage = IMAGEMANAGER->FindImage(L"Condition");
	SetConditionImage();


	IMAGEMANAGER->LoadFromFile(mFileName, Resources(mFileName + L".bmp"), 960, 512, 30, 16, true);
	mImage = IMAGEMANAGER->FindImage(mFileName);

	mRenderSizeX = mImage->GetFrameWidth() * 2;
	mRenderSizeY = mImage->GetFrameHeight() * 2;

	mCost = 150 + (mAtk + mDef) * 10;
	
}

void Staff::Release()
{
	
}

void Staff::Update()
{
	SetConditionImage();
}

void Staff::Render(HDC hdc)
{

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
	case Character::None:
		comment = L" "; //����ִ� Ư��(ǥ�� ���ϴ� ����)
		break;
	default:
		break;
	}
	return comment;
}

wstring Staff::GetCharInfo(int Charnum)
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
		comment = L"�ƹ� Ư�� ����";
		break;
	case Character::Hero:	
		comment = L"�̱�� ������ ��� �ɷ�ġ -10, ���� ������ +10";
		break;
	case Character::Glass:	
		comment = L"�̱�� ������ ��� �ɷ�ġ +10, ���� ������ -10";
		break;
	case Character::Mother:	
		comment = L"ȸ���� + 10";
		break;
	case Character::Thorn:	
		comment = L"������ ȸ���� -10";
		break;
	case Character::Winner:	
		comment = L"óġ����(assist)�� ü�� +10";
		break;
	case Character::Distraction:
		comment = L"���ݴ���� 5�ʸ��� �������� ����";
		break;
	case Character::Fest:	
		comment = L"��ų �����ӵ� 10% ����";
		break;
	case Character::Spear:
		comment = L"���� ����ȿ�� +10 (������ ������ 10 ����)";
		break;
	case Character::None:
		comment = L" ";
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
		mConditionX = 4;
		break;
	case Condition::LittleBad:
		mConditionX = 3;
		break;
	case Condition::Nomal:
		mConditionX = 2;
		break;
	case Condition::Good:
		mConditionX = 1;
		break;
	case Condition::Best:
		mConditionX = 0;
		break;
	}
}

Staff::Staff(const Staff & copy)
	:GameObject(copy)
{
	mStaffName = copy.mStaffName;
	mImage = copy.mImage;

	mFileName = copy.mFileName;
	mTeamName = copy.mTeamName;
	mAtk = copy.mAtk;
	mDef = copy.mDef;
	mHeal = copy.mHeal;

	mMostChamp.insert(copy.mMostChamp.begin(), copy.mMostChamp.end());

	mChar1 = copy.mChar1;
	mChar2 = copy.mChar2;
	mTrainingPoint = copy.mTrainingPoint;
	mRandomIndexX = copy.mRandomIndexX;
	mRandomIndexY = copy.mRandomIndexY;
	mCondition = copy.mCondition;
	mConditionX = copy.mConditionX;
	mRenderSizeX = copy.mRenderSizeX;
	mRenderSizeY = copy.mRenderSizeY;
	mStatPoint = copy.mStatPoint;
	mConditionImage = copy.mConditionImage;
	mConditionX = copy.mConditionX;
	mCost = copy.mCost;

}

Staff & Staff::operator=(const Staff & copy)
{
	mStaffName = copy.mStaffName;
	mImage = copy.mImage;

	mFileName = copy.mFileName;
	mTeamName = copy.mTeamName;
	mAtk = copy.mAtk;
	mDef = copy.mDef;
	mHeal = copy.mHeal;

	
	mMostChamp.insert(copy.mMostChamp.begin(), copy.mMostChamp.end());

	mChar1 = copy.mChar1;
	mChar2 = copy.mChar2;
	mTrainingPoint = copy.mTrainingPoint;
	mRandomIndexX = copy.mRandomIndexX;
	mRandomIndexY = copy.mRandomIndexY;
	mCondition = copy.mCondition;
	mConditionX = copy.mConditionX;
	mRenderSizeX = copy.mRenderSizeX;
	mRenderSizeY = copy.mRenderSizeY;
	mStatPoint = copy.mStatPoint;
	mConditionImage = copy.mConditionImage;
	mConditionX = copy.mConditionX;
	mCost =	copy.mCost;

	return *this;
}
