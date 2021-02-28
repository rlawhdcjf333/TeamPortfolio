#pragma once
#include "GameObject.h"
class Animation;
enum class ClassType : int
{
	Warrior = 0,
	ADCarry = 1,
	Magician = 2,
	Supporter = 3,
	Assassin = 4,

	End
};
class Champ : public GameObject
{
protected:
	Image* mImage;
	Image* mSkillImage;
	Image* mSpecialSkillImage;

	Animation* mCurrentAnm;
	map<wstring ,Animation*> mAnimationList;
	wstring mChampName;
	wstring mChampEx;
	wstring mSkillEx;
	wstring mSpecialSkillEx;
	

	ClassType mClassType;



	float mFullHP;			//�¾ �� Ǯ�Ƿ� �¾�� ���ֱ� ����.
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
	float mSkill;			//��ų1

	float mAttackCool;		//���� �� Ÿ��
	float mSkill1Cool;		//��ų1 �� Ÿ��
	float mDeathCool;		//���� �� Ÿ��


	float mAlpha;
	GameObject* mTarget;	//�޾ƿ� Ÿ�� ������
	GameObject* mStaff;		//�޾ƿ� ���� ������
	vector<GameObject*> mPlayerList;			//�Ʊ��� (�ִ� 3��)
	vector<GameObject*> mEnemyList;				//����	 (�ִ� 3��)

	int mImageAnimationFrame;

public:
	Champ(const string& name);
	Champ(const string& name, float x, float y);
	Champ(const string& name, int animation);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void UIRender(HDC  hdc, int startX, int startY, int width, int height); //UI�� ����

	void ChampImageRender(HDC hdc, RECT rc);
	void SkillImageRender(HDC hdc, RECT rc);
	void SpecialSkillImageRender(HDC hdc, RECT rc);

	void SetStaff(GameObject* staff) { mStaff = staff; } //staff �ҷ�����
	void SetHP(float hp) { mHP = hp; } //HP�� �ҷ�����
	float GetHP() { return mHP; } //HP�� ����

	float GetAtk() { return mAtk; }
	float GetAtkCool() { return mAttackCool; }
	float GetRange() { return mRange; }
	float GetDef() { return mDef; }
	float GetSpeed() { return mSpeed; }
	float GetSkillCool() { return mSkill1Cool; }
	float GetSpecialSkillCool() { return mSpecialSkill; }

	GameObject* GetStaff() { return mStaff; } //staff�� ����
	vector<GameObject*> GetPlayerList() { return mPlayerList; }
	vector<GameObject*> GetEnemyList() { return mEnemyList; }
	ClassType GetClassType() const { return mClassType; }
	wstring GetChampName() const { return mChampName; }
	wstring GetChampEx() const& { return mChampEx; }
	wstring GetSkillEx() const { return mSkillEx; }
	wstring GetSpecialSkillEx() const { return mSpecialSkillEx; }
	
	//float GetChampAnm() { return }
	float GetFullHP() { return mFullHP; }			//UIǥ��
	void Recover() { mHP = mFullHP;  }				//�׾����� �̰� ���� �ٽ� Ǯü��
};