#pragma once
#include "GameObject.h"
class Champ;
class Animation;

enum class Character : int	//0 ~ 8, 9�� ǥ�þ���
{
	Nomal,	//��� : �ƹ� Ư�� ����
	Hero,	//���� : �̱�� ������ ��� �ɷ�ġ -10, ���� ������ +10
	Glass,	//������Ż : �̱�� ������ ��� �ɷ�ġ +10, ���� ������ -10
	Mother,	//���� : ȸ���� + 10
	Thorn,	//���� : ������ ȸ���� -10
	Winner,	//�¸��� : óġ����(assist)�� ü�� +10
	Distraction,//���ǻ길 : ���ݴ���� 5�ʸ��� �������� ����
	Fest,	//��� : ��ų �����ӵ� 10% ����
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
class Staff : public GameObject
{


protected:
	string mStaffName;
	Image* mImage;
	map <wstring, Animation*> mAnimationList;
	Animation* mCurrentAnm;

	wstring mFileName;
	wstring mTeamName;

	int mAtk;	//���ݷ�
	int mDef;	//����
	int mHeal;//ȸ����

	map<string, int>mMostChamp;	//first = champName, second = ���õ� ����ġ?	//���࿡ ��Ʈ���̸� �ɷ�ġ�� second(���õ� ����ġ)��ŭ ���� ��Ŵ

	Character mChar1;	//if(Character::None) ǥ�� ����
	Character mChar2;	//if(Character::None) ǥ�� ����

	int mTraningPoint;	//Scene1:Home ���� �Ʒÿ� ���� ����, ���� �־���ϳ�? Scene1::Home���� ���°Ŷ� �ʿ������ ���ֵ� ��
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
	
	string GetStaffName() { return mStaffName; }

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
	Character GetChar1() { return mChar1; }
	Character GetChar2() { return mChar2; }
	wstring GetCharComment(int Charnum);

	void SetProficiency(string key, int value) { mMostChamp.find(key)->second = value; }
	int GetProficiency(string key)const { return mMostChamp.find(key)->second; }
	void UpProficiency(string key, int value) { mMostChamp.find(key)->second += value; }	//scene1::Home ���� ���� �ɵ�?

	void SetRenderSize(int x, int y) { mRenderSizeX = x, mRenderSizeY = y; }

	void SetConditionImage();
	
	map<string, int> GetMostChamp() { return mMostChamp; }

	int GetTrainingPoint() { return mTraningPoint; }
	void SetTrainingPoint(int val) { mTraningPoint = val; }
	void MinusTrainingPoint() { mTraningPoint--; }
	void PlusTrainingPoint() { mTraningPoint++; }

	void PlusAtk() { mAtk++; }
	void PlusDef() { mDef++; }
	void MinusAtk() { mAtk--;}
	void MinusDef() { mDef--; }


public:
	Staff(const Staff& copy); //���� ������ �����ε� deep copy�� �ʿ�. ���ο� ���� ����� �ݵ�� ����ٰ��� �߰��ؾ���
	Staff& operator= (const Staff& copy); //���� ������ �����ε�. �� Ŭ������ ���ο� ������ ����� �ݵ�� ����ٰ��� �߰��ؾ���


};

