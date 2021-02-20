#pragma once
#include "GameObject.h"
class Champ;
class Animation;

enum class Character	//0 ~ 8, 9�� ǥ�þ���
{
	Nomal,	//��� : �ƹ� Ư�� ����
	Hero,	//���� : �̱�� ������ ��� �ɷ�ġ -10, ���� ������ +10
	Glass,	//������Ż : �̱�� ������ ��� �ɷ�ġ +10, ���� ������ -10
	Mother,	//���� : ���� + 10
	Thorn,	//���� : ������ ���� -10
	Winner,	//�¸��� : óġ����(assist)�� ü�� +10
	Distraction,//���ǻ길 : ���ݴ���� 5�ʸ��� �������� ����
	Fest,	//���� : ��ų �����ӵ� 10% ����
	Spear,	//��մ� â : ���� ����ȿ�� +10(������ ������ 10 �����Ѵ�)

	None	//����ִ� Ư��(ǥ�� ���ϴ� ����)
};

class Staff : public GameObject
{
	Image* mImage;
	map <wstring, Animation*> mAnimationList;
	Animation* mCurrentAnm;

	float mAtk;	//���ݷ�
	float mDef;	//����

	map<wstring, int>mMostChamp;	//first = champName, second = ���õ� ����ġ?	//���࿡ ��Ʈ���̸� �ɷ�ġ�� second(���õ� ����ġ)��ŭ ���� ��Ŵ

	Character mChar1;	//if(Character::None) ǥ�� ����
	Character mChar2;	//if(Character::None) ǥ�� ����

	int mTraningPoint;	//Scene1:Home ���� �Ʒÿ� ���� ����, ���� �־���ϳ�? Scene1::Home���� ���°Ŷ� �ʿ������ ���ֵ� ��

public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

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

