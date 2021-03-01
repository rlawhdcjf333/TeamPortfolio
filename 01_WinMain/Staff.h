#pragma once
#include "GameObject.h"
class Champ;
class Animation;

enum class Character : int	//0 ~ 8, 9�� ǥ�þ���
{
	Normal,	//��� : �ƹ� Ư�� ����
	Hero,	//���� : �̱�� ������ ��� �ɷ�ġ -10, ���� ������ +10
	Glass,	//������Ż : �̱�� ������ ��� �ɷ�ġ +10, ���� ������ -10
	Mother,	//���� : ȸ���� + 10
	Thorn,	//���� : ������ ȸ���� -10
	Winner,	//�¸��� : óġ����(assist)�� ü�� +10
	Distraction,//���ǻ길 : ���ݴ���� 5�ʸ��� �������� ����
	Fast,	//��� : ��ų �����ӵ� 10% ����
	Spear,	//��մ� â : ���� ����ȿ�� +10(������ ������ 10 �����Ѵ�)

	None	//����ִ� Ư��(ǥ�� ���ϴ� ����)
};

enum class Condition : int
{
	Bad,	//�־�
	LittleBad,//�ణ ������
	Nomal,	//����
	Good,	//�ణ ����
	Best	//�ְ�
};
class  Staff: public GameObject
{


protected:
	string mStaffName;
	Image* mImage;

	wstring mFileName;
	wstring mTeamName;

	int mAtk;	//���ݷ�
	int mDef;	//����
	int mHeal;//ȸ����

	map<string, int>mMostChamp;	//first = champName, second = ���õ� ����ġ?	//���࿡ ��Ʈ���̸� �ɷ�ġ�� second(���õ� ����ġ)��ŭ ���� ��Ŵ

	Character mChar1;	//if(Character::None) ǥ�� ����
	Character mChar2;	//if(Character::None) ǥ�� ����

	int mTrainingPoint;	//Scene1:Home ���� �Ʒÿ� ���� ����, ���� �־���ϳ�? Scene1::Home���� ���°Ŷ� �ʿ������ ���ֵ� ��
	int mRandomIndexX;	//�̹��� ���� ����
	int mRandomIndexY;	//�̹��� ���� ����

	Condition mCondition;	//�����

	int mRenderSizeX;
	int mRenderSizeY;

	int mStatPoint;
	
	Image* mConditionImage;
	int mConditionX;

	int mCost; // ���� ��� ���鋚 ���

public:
	Staff(const string& name, const string& staffName, const wstring& teamName);
	
	string GetStaffName()const { return mStaffName; }

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void UIRender(HDC hdc, int startX, int startY, int width, int height);
	void ConditionRender(HDC hdc, int startX, int startY, int width, int height);

	inline int GetAtk()const { return mAtk; }
	inline void SetAtk(float atk) { mAtk = atk; }
	inline int GetDef()const { return mDef; }
	inline void SetDef(float def) { mDef = def; }
	void UpAtk(int n = 2) { mAtk += n; }
	void UpDef(int n = 2) { mAtk += n; }

	void SetChar1(Character c) { mChar1 = c; }
	void SetChar2(Character c) { mChar2 = c; }
	
	Character GetChar1()const { return mChar1; }
	Character GetChar2()const { return mChar2; }
	
	wstring GetCharComment(int Charnum);
	wstring GetCharInfo(int Charnum);

	void SetProficiency(string key, int value) { mMostChamp.find(key)->second = value; }
	int GetProficiency(string key)const { return mMostChamp.find(key)->second; }
	void UpProficiency(string key, int value) { mMostChamp.find(key)->second += value; }	//scene1::Home ���� ���� �ɵ�?

	void SetRenderSize(int x, int y) { mRenderSizeX = x, mRenderSizeY = y; }

	void SetConditionImage();
	void RandomCondition() { mCondition = (Condition)Random::GetInstance()->RandomInt(4); };

	map<string, int> GetMostChamp() { return mMostChamp; }

	int GetTrainingPoint()const { return mTrainingPoint; }
	void SetTrainingPoint(int val) { mTrainingPoint = val; }
	void MinusTrainingPoint() { mTrainingPoint--; }
	void PlusTrainingPoint() { mTrainingPoint++; }

	void PlusAtk() { mAtk++; }
	void PlusDef() { mDef++; }
	void MinusAtk() { mAtk--;}
	void MinusDef() { mDef--; }

	void PlusMost1() 
	{
		mMostChamp[mMostChamp.begin()->first] = mMostChamp.begin()->second + 1;
	}
	void MinusMost1()
	{
		mMostChamp[mMostChamp.begin()->first] = mMostChamp.begin()->second - 1;
	}
	void PlusMost2()
	{
		mMostChamp[mMostChamp.rbegin()->first] = mMostChamp.rbegin()->second + 1;
	}
	void MinusMost2()
	{
		mMostChamp[mMostChamp.rbegin()->first] = mMostChamp.rbegin()->second - 1;
	}
	Condition GetCondition()const { return mCondition; }
	void SetCondition(Condition con) { mCondition = con; }

	int GetCost() { return mCost; }

	Director* GetMyDirector();

public:
	Staff(const Staff& copy); //���� ������ �����ε� deep copy�� �ʿ�. ���ο� ���� ����� �ݵ�� ����ٰ��� �߰��ؾ���
	Staff& operator= (const Staff& copy); //���� ������ �����ε�. �� Ŭ������ ���ο� ������ ����� �ݵ�� ����ٰ��� �߰��ؾ���


};

