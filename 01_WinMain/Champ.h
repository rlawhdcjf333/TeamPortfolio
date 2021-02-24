#pragma once
#include "GameObject.h"
class Animation;
enum class Tag : int
{
	Assassin =0,
	Tanker,
	Diller,
	Brujer
};
class Champ : public GameObject
{
protected:
	Image* mImage;

	Animation* mCurrentAnm;
	map<wstring ,Animation*> mAnimationList;

	float mHP;				//���� HP
	float mMP;				//���� MP
	float mMPSecGet;		//�ʴ� ���� ����
	float mMPAtkGet;		//���ݽ� ���� ����
	float mMPHitGet;		//�ǰݽ� ���� ����			���� �̷��� 3���� �ʿ��ұ� �Ѱ��� ������ ������ ������ ������ ������...
	float mAtk;				//���� ���ݷ�
	float mDef;				//���� ����
	float mDistance1;		//��1���� �Ÿ�
	float mDistance2;		//��2���� �Ÿ�
	float mDistance3;		//��3���� �Ÿ�
	float mTargetDistance;	//Ÿ�ٰ��� �Ÿ�
	float mAngle;			//Ÿ�ٰ��� ����
	float mRange;			//è�� ���� ��Ÿ�
	float mSpeed;			//�ʴ� �̵��ӵ�
	float mSpecialSkill;	//�ñر�
	float mSkill;

	float mAttackCool;		//���� �� Ÿ��
	float mSkill1Cool;		//��ų1 �� Ÿ��
	float mDeathCool;		//���� �� Ÿ��


	float mAlpha;
	GameObject* mTarget;	//�޾ƿ� Ÿ�� ������
	GameObject* mStaff;		//�޾ƿ� ���� ������
	vector<GameObject*> mPlayerList;
	vector<GameObject*> mEnemyList;

	
	float mFullHP;
public:
	Champ(const string& name);
	Champ(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


	void SetStaff(GameObject* staff) { mStaff = staff; } //staff �ҷ�����
	void SetHP(float hp) { mHP = hp; } //HP�� �ҷ�����
	float GetHP() { return mHP; } //HP�� ����

	GameObject* GetStaff() { return mStaff; } //staff�� ����
	vector<GameObject*> GetPlayerList() { return mPlayerList; }
	vector<GameObject*> GetEnemyList() { return mEnemyList; }
	
	float GetFullHP() { return mFullHP; }			//UIǥ��
	void Recover() { mHP = mFullHP;  }	//�׾����� �̰� ���� �ٽ� Ǯü��
};