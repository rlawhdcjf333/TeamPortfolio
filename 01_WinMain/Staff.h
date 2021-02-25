#pragma once
#include "GameObject.h"
class Champ;
class Animation;

enum class Character : int	//0 ~ 8, 9는 표시안함
{
	Nomal,	//평범 : 아무 특성 없음
	Hero,	//영웅 : 이기고 있을때 모든 능력치 -10, 지고 있을때 +10
	Glass,	//유리멘탈 : 이기고 있을때 모든 능력치 +10, 지고 있을때 -10
	Mother,	//엄마 : 회복력 + 10
	Thorn,	//가시 : 상대방의 회복력 -10
	Winner,	//승리자 : 처치관여(assist)시 체력 +10
	Distraction,//주의산만 : 공격대상이 5초마다 무작위로 변경
	Fest,	//쾌속 : 스킬 시전속도 10% 증가
	Spear,	//꿰뚫는 창 : 방어력 관통효과 +10(상대방의 방어력을 10 무시한다)

	None	//비어있는 특성(표시 안하는 상태)
};

enum class Condition : int
{
	Bad,	//최악
	LittleBad,//약간 안좋음
	Nomal,	//보통
	Good,	//약간 좋음
	Best	//최고
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

	int mAtk;	//공격력
	int mDef;	//방어력
	int mHeal;//회복력

	map<string, int>mMostChamp;	//first = champName, second = 숙련도 가중치?	//만약에 모스트픽이면 능력치를 second(숙련도 가중치)만큼 증가 시킴

	Character mChar1;	//if(Character::None) 표시 안함
	Character mChar2;	//if(Character::None) 표시 안함

	int mTraningPoint;	//Scene1:Home 에서 훈련에 쓰일 변수, 여기 있어야하나? Scene1::Home에서 쓰는거라 필요없으면 없애도 됨
	int mRandomIndexX;	//이미지 랜덤 변수
	int mRandomIndexY;	//이미지 랜덤 변수

	Condition mCondition;	//컨디션

	int mRenderSizeX;
	int mRenderSizeY;

	int mStatPoint;
	
	Image* mConditionImage;
	int mConditionX;

	int mCost; // 재계약 비용 만들떄 사용
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
	void UpProficiency(string key, int value) { mMostChamp.find(key)->second += value; }	//scene1::Home 에서 쓰면 될듯?

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
	Staff(const Staff& copy); //복사 생성자 오버로딩 deep copy에 필요. 새로운 변수 생기면 반드시 여기다가도 추가해야함
	Staff& operator= (const Staff& copy); //복사 연산자 오버로딩. 이 클래스에 새로운 변수가 생기면 반드시 여기다가도 추가해야함


};

