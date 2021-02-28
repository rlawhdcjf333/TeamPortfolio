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

	ClassType mClassType;



	float mFullHP;			//태어날 때 풀피로 태어나게 해주기 위함.
	float mHP;				//나의 HP
	float mMP;				//나의 MP
	float mMPSecGet;		//초당 얻을 마나
	float mMPAtkGet;		//공격시 얻을 마나
	float mMPHitGet;		//피격시 얻을 마나			굳이 이렇게 3개가 필요할까 한개의 변수로 돌려서 쓸수도 있을것 같은데...
	float mAtk;				//나의 공격력
	float mDef;				//나의 방어력
	float mDistance1;		//적1과의 거리
	float mDistance2;		//적2와의 거리
	float mDistance3;		//적3과의 거리
	float mTargetDistance;	//타겟과의 거리
	float mAngle;			//타겟과의 각도
	float mRange;			//챔프 공격 사거리
	float mSpeed;			//초당 이동속도
	float mSpecialSkill;	//궁극기
	float mSkill;			//스킬1

	float mAttackCool;		//공격 쿨 타임
	float mSkill1Cool;		//스킬1 쿨 타임
	float mDeathCool;		//데스 쿨 타임


	float mAlpha;
	GameObject* mTarget;	//받아올 타겟 포인터
	GameObject* mStaff;		//받아올 스텝 포인터
	vector<GameObject*> mPlayerList;			//아군들 (최대 3명)
	vector<GameObject*> mEnemyList;				//적들	 (최대 3명)

	int mImageAnimationFrame;

public:
	Champ(const string& name);
	Champ(const string& name, float x, float y);
	Champ(const string& name, int animation);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void UIRender(HDC  hdc, int startX, int startY, int width, int height); //UI용 렌더

	void ChampImageRender(HDC hdc, RECT rc);

	void SetStaff(GameObject* staff) { mStaff = staff; } //staff 불러오기
	void SetHP(float hp) { mHP = hp; } //HP값 불러오기
	float GetHP() { return mHP; } //HP값 조정

	float GetAtk() { return mAtk; }
	float GetAtkCool() { return mAttackCool; }
	float GetRange() { return mRange; }
	float GetDef() { return mDef; }
	float GetSpeed() { return mSpeed; }

	GameObject* GetStaff() { return mStaff; } //staff값 조정
	vector<GameObject*> GetPlayerList() { return mPlayerList; }
	vector<GameObject*> GetEnemyList() { return mEnemyList; }
	ClassType GetClassType() const { return mClassType; }
	wstring GetChampName() const { return mChampName; }
	wstring GetChampEx() const& { return mChampEx; }
	
	//float GetChampAnm() { return }
	float GetFullHP() { return mFullHP; }			//UI표시
	void Recover() { mHP = mFullHP;  }				//죽었을때 이걸 쓰면 다시 풀체력

	void StaffOnChamp();


};