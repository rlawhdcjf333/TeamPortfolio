#pragma once
#include "GameObject.h"

// 선수 리스트
class Staff;
class Director : public GameObject
{
	vector<string> mRandomNameList; 

	Image* mTeamImage;
	wstring mFileName;
	wstring mTeamName;
	int mMonth;
	int mWeek;
	int mGold;

	int mWin;
	int mLose;
	int mLeagueScore;

	vector<string> mStaffNameList;
public:
	Director(const string& name, const wstring& fileName, const wstring& teamName);

	string RandomName();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void UIRender(HDC hdc, int startX, int startY, int width, int height);


	void SetStaffNameList(vector<string> staffNameList) { mStaffNameList = staffNameList; }
	vector<string> GetStaffNameList() { return mStaffNameList; }

public:
	Director(const Director& copy); //복사 생성자 오버로딩, 스토리지 용
	Director& operator=(const Director& copy); //  복사연산자 오버로딩 촉수엄금, 차후 변수가 추가되면 여기에다가도 추가해야 신전환에 복사가 될거임
};