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

	Image* mImage;
	map <wstring, Animation*> mAnimationList;
	Animation* mCurrentAnm;

	wstring mFileName;

	float mAtk;	//���ݷ�
	float mDef;	//����
	float mHeal;//ȸ����

	map<wstring, int>mMostChamp;	//first = champName, second = ���õ� ����ġ?	//���࿡ ��Ʈ���̸� �ɷ�ġ�� second(���õ� ����ġ)��ŭ ���� ��Ŵ

	Character mChar1;	//if(Character::None) ǥ�� ����
	Character mChar2;	//if(Character::None) ǥ�� ����

	int mTraningPoint;	//Scene1:Home ���� �Ʒÿ� ���� ����, ���� �־���ϳ�? Scene1::Home���� ���°Ŷ� �ʿ������ ���ֵ� ��
	int mRandomIndexX;	//�̹��� ���� ����
	int mRandomIndexY;	//�̹��� ���� ����

	Condition mCondition;	//�����
public:
	Staff(const string& name, const wstring& fileName);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	string RandomName();

	inline float GetAtk()const { return mAtk; }
	inline void SetAtk(float atk) { mAtk = atk; }
	inline float GetDef()const { return mDef; }
	inline void SetDef(float def) { mDef = def; }

	void SetChar1(Character c) { mChar1 = c; }
	void SetChar2(Character c) { mChar2 = c; }
	Character GetChar1() { return mChar1; }
	Character GetChar2() { return mChar2; }

	void SetProficiency(wstring key, int value) { mMostChamp.find(key)->second = value; }
	int GetProficiency(wstring key)const { return mMostChamp.find(key)->second; }
	void AddProficiency(wstring key, int value) { mMostChamp.find(key)->second += value; }	//scene1::Home ���� ���� �ɵ�?
};

