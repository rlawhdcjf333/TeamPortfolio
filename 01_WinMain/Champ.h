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



	float mMaxHP;			//나의 풀 피
	float mMaxMP;			//나의 풀 마나
	float mHP;				//나의 현재 HP
	float mMP;				//나의 MP
	float mInitAtk;
	float mAtk;				//나의 공격력
	float mInitDef;
	float mDef;				//나의 방어력
	float mInitHealPr;
	float mHealPr;			//나의 힐능력
	float mDistance1;		//적1과의 거리
	float mDistance2;		//적2와의 거리
	float mDistance3;		//적3과의 거리
	float mTargetDistance;	//타겟과의 거리
	float mAngle;			//타겟과의 각도
	float mRange;			//챔프 공격 사거리
	float mSpeed;			//초당 이동속도
	float mRespawnX;
	float mRespawnY;
	float mMaxAttackCool;
	float mAttackCool;		//공격 쿨 타임
	float mMaxSkill1Cool;
	float mSkill1Cool;		//스킬1 쿨 타임
	float mDeathCool;		//데스 쿨 타임
	int mDeathCount;		//데스 세는거
	bool mIsDeath;
	bool mIsAction;

	bool mIsNuckback;
	float mNuckbackForce;	//넉백 함수
	float mNuckbackAngle;

	bool mIsAtkBuff;
	float mAtkBuff;			//공격력 버프 함수
	float mAtkBuffTime;

	bool mIsDefBuff;
	bool mGetDefBuff;
	float mDefBuff;			//단체 방어력 버프 함수
	float mDefBuffTime;

	bool mIsAggro;
	bool mProvocateur;		//도발 함수
	float mAggroTime;

	bool mIsDefPierce; //방어 관통 함수

	bool mTargetStatus; //타겟 생사여부 캐싱
	int mAssistCount; //어시스트 계산
	bool mWinnerTrigger; //승자 특성

	bool mThornTrigger; //가시 특성

	float mDistractionDuration; //산만 특성
	bool mDistractionTrigger;

	Image* mHPBar;
	Image* mHPImage;
	Image* mMPImage;
	Image* mExclamation;
	Image* mDefImage;
	Image*mSkillImage;
	Image*mSpecialSkillImage;
	float mAlpha;
	GameObject* mTarget;	//받아올 타겟 포인터
	GameObject* mStaff;		//받아올 스텝 포인터
	vector<GameObject*> mFriendList;			//아군들 (최대 3명)
	vector<GameObject*> mEnemyList;				//적들	 (최대 3명)

	int mImageAnimationFrame;

public:
	Champ(const string& name);
	Champ(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void UIRender(HDC  hdc, int startX, int startY, int width, int height); //UI용 렌더
	void ChampImageRender(HDC hdc, RECT rc);
	void SkillImageRender(HDC hdc, RECT rc);
	void SpecialSkillImageRender(HDC hdc, RECT rc);


	void SetStaff(GameObject* staff) { mStaff = staff; } //staff 불러오기
	void SetHP(float hp) { mHP = hp; } //HP값 불러오기
	void SetTarget(GameObject* target) { mTarget = target; }
	void SetProvocateur(bool aggro) { mProvocateur = aggro; }
	void SetDef(float def) { mDef = def; }
	void SetGetDefBuff(float def) { mGetDefBuff = def; }
	void SetEnemyList(vector <GameObject*> list) { mEnemyList.assign(list.begin(),list.end()); }
	void SetFriendList(vector <GameObject*> list) { mFriendList.assign(list.begin(), list.end()); }
	void SetHealPr(float val) { mHealPr = val; }


	float GetHP() { return mHP; } //HP값 조정
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

	GameObject* GetStaff() { return mStaff; } //staff값 조정
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
	

	void StaffOnChamp(); //경기 시작전 챔프를 스태프의 특성값으로 업데이트하는 함수
	void DefPierce();
	float GetInitDef() { return mInitDef; }

	void WinnerFunc();

	void ThornFunc();
	void Distraction();

	void SetXY(int x, int y);
};