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
	Fest,	//���� : ��ų �����ӵ� 10% ����
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
	static vector<string>Name;

	string mStaffName;

	Image* mImage;
	map <wstring, Animation*> mAnimationList;
	Animation* mCurrentAnm;

	wstring mFileName;

	float mAtk;	//���ݷ�
	float mDef;	//����
	float mHeal;//ȸ����

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

public:
	Staff(const string& name, const wstring& fileName);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void UIRender(HDC hdc, int startX, int startY, int width, int height);

	string RandomName();

	inline float GetAtk()const { return mAtk; }
	inline void SetAtk(float atk) { mAtk = atk; }
	inline float GetDef()const { return mDef; }
	inline void SetDef(float def) { mDef = def; }
	void UpAtk(int n = 2) { mAtk += n; }
	void UpDef(int n = 2) { mAtk += n; }

	void SetChar1(Character c) { mChar1 = c; }
	void SetChar2(Character c) { mChar2 = c; }
	Character GetChar1() { return mChar1; }
	Character GetChar2() { return mChar2; }

	void SetProficiency(string key, int value) { mMostChamp.find(key)->second = value; }
	int GetProficiency(string key)const { return mMostChamp.find(key)->second; }
	void UpProficiency(string key, int value) { mMostChamp.find(key)->second += value; }	//scene1::Home ���� ���� �ɵ�?

	void SetRenderSize(int x, int y) { mRenderSizeX = x, mRenderSizeY = y; }

};

