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

	Animation* mCurrentAnm;
	map<wstring ,Animation*> mAnimationList;
	wstring mChampName;
	wstring mChampEx;
	wstring mSkillEx;
	wstring mSpecialSkillEx;
	

	ClassType mClassType;



	float mMaxHP;			//���� Ǯ ��
	float mMaxMP;			//���� Ǯ ����
	float mHP;				//���� ���� HP
	float mMP;				//���� MP
	float mInitAtk;
	float mAtk;				//���� ���ݷ�
	float mInitDef;
	float mDef;				//���� ����
	float mInitHealPr;
	float mHealPr;			//���� ���ɷ�
	float mDistance1;		//��1���� �Ÿ�
	float mDistance2;		//��2���� �Ÿ�
	float mDistance3;		//��3���� �Ÿ�
	float mTargetDistance;	//Ÿ�ٰ��� �Ÿ�
	float mAngle;			//Ÿ�ٰ��� ����
	float mRange;			//è�� ���� ��Ÿ�
	float mSpeed;			//�ʴ� �̵��ӵ�
	float mRespawnX;
	float mRespawnY;
	float mMaxAttackCool;
	float mAttackCool;		//���� �� Ÿ��
	float mMaxSkill1Cool;
	float mSkill1Cool;		//��ų1 �� Ÿ��
	float mDeathCool;		//���� �� Ÿ��
	int mDeathCount;		//���� ���°�
	bool mIsDeath;
	bool mIsAction;

	bool mIsNuckback;
	float mNuckbackForce;	//�˹� �Լ�
	float mNuckbackAngle;

	bool mIsAtkBuff;
	float mAtkBuff;			//���ݷ� ���� �Լ�
	float mAtkBuffTime;

	bool mIsDefBuff;
	bool mGetDefBuff;
	float mDefBuff;			//��ü ���� ���� �Լ�
	float mDefBuffTime;

	bool mIsAggro;
	bool mProvocateur;		//���� �Լ�
	float mAggroTime;

	bool mIsDefPierce; //��� ���� �Լ�

	bool mTargetStatus; //Ÿ�� ���翩�� ĳ��
	int mAssistCount; //��ý�Ʈ ���
	bool mWinnerTrigger; //���� Ư��

	bool mThornTrigger; //���� Ư��

	float mDistractionDuration; //�길 Ư��
	bool mDistractionTrigger;

	Image* mHPBar;
	Image* mHPImage;
	Image* mMPImage;
	Image* mExclamation;
	Image* mDefImage;
	Image*mSkillImage;
	Image*mSpecialSkillImage;
	float mAlpha;
	GameObject* mTarget;	//�޾ƿ� Ÿ�� ������
	GameObject* mStaff;		//�޾ƿ� ���� ������
	vector<GameObject*> mFriendList;			//�Ʊ��� (�ִ� 3��)
	vector<GameObject*> mEnemyList;				//����	 (�ִ� 3��)

	int mImageAnimationFrame;

public:
	Champ(const string& name);
	Champ(const string& name, float x, float y);

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
	void SetTarget(GameObject* target) { mTarget = target; }
	void SetProvocateur(bool aggro) { mProvocateur = aggro; }
	void SetDef(float def) { mDef = def; }
	void SetGetDefBuff(float def) { mGetDefBuff = def; }
	void SetEnemyList(vector <GameObject*> list) { mEnemyList.assign(list.begin(),list.end()); }
	void SetFriendList(vector <GameObject*> list) { mFriendList.assign(list.begin(), list.end()); }
	void SetHealPr(float val) { mHealPr = val; }


	float GetHP() { return mHP; } //HP�� ����
	float GetAtk() { return mAtk; }
	float GetAtkCool() { return mAttackCool; }
	float GetRange() { return mRange; }
	float GetDef() { return mDef; }
	float GetSpeed() { return mSpeed; }
	bool GetIsDeath() { return mIsDeath; }
	float GetSkillCool() { return mSkill1Cool; }
	float GetHealPr() { return mHealPr; }
	float GetInitHealPr() { return mInitHealPr; }
	int GetDeathCount() { return mDeathCount; }

	GameObject* GetStaff() { return mStaff; } //staff�� ����
	vector<GameObject*> GetPlayerList() { return mFriendList; }
	vector<GameObject*> GetEnemyList() { return mEnemyList; }
	ClassType GetClassType() const { return mClassType; }
	wstring GetChampName() const { return mChampName; }
	wstring GetChampEx() const& { return mChampEx; }

	void NuckBack(float force, float angle);
	void AtkBuff(float atkbuff, float time);
	void Aggro(float time);
	void DefBuff(float defbuff, float time);
	wstring GetSkillEx() const { return mSkillEx; }
	wstring GetSpecialSkillEx() const { return mSpecialSkillEx; }
	

	void StaffOnChamp(); //��� ������ è���� �������� Ư�������� ������Ʈ�ϴ� �Լ�
	void DefPierce();
	float GetInitDef() { return mInitDef; }

	void WinnerFunc();

	void ThornFunc();
	void Distraction();

	void SetXY(int x, int y);
};