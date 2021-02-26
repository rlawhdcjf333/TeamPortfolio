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

	int mRound;
	int mMonth;
	int mWeek;
	int mGold;

	int mRank;
	int mWin;
	int mLose;
	int mLeagueScore;

	int mTeamTotalKill;
	int mTeamTotalDeath;

	vector<string> mStaffNameList;
public:
	Director(const string& name, const wstring& fileName, const wstring& teamName);

	string RandomName();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetRound(int round) { mRound = round; }
	void UpRound() { mRound++; }
	void SetMonth(int month) { mMonth = month; }
	void SetWeek(int week) { mWeek = week; }
	void SetGold(int gold) { mGold = gold; }

	int GetRound() { return mRound; }
	int GetMonth() { return mMonth; }
	int GetWeek() { return mWeek; }
	int GetGold() { return mGold; }

	void UIRender(HDC hdc, int startX, int startY, int width, int height);
	void TeamImageRender(HDC hdc, int startX, int startY, int widht, int height);
	void TeamImageRender(HDC hdc, RECT rc);

	wstring GetTeamName() { return mTeamName; }

	void SetRank(int rank) { mRank = rank; }
	void SetWin(int win) { mWin = win; }
	void SetLose(int lose) { mLose = lose; }
	void SetLeagueScore(int leagueScore) { mLeagueScore = leagueScore; }
	int GetRank() { return mRank; }
	int GetWin() { return mWin; }
	int GetLose() { return mLose; }
	int GetLeagueScore() { return mLeagueScore; }

	void SetTeamTotalKill(int teamTotalKill) { mTeamTotalKill = teamTotalKill; }
	void SetTeamTotalDeath(int teamTotalDeath) { mTeamTotalDeath = teamTotalDeath; }
	int GetTeamTotalKill() { return mTeamTotalKill; }
	int GetTeamTotalDeath() { return mTeamTotalDeath; }

	vector<string> GetStaffNameList() { return mStaffNameList; }

	void AddStaff(string name);

public:
	Director(const Director& copy); //복사 생성자 오버로딩, 스토리지 용
	Director& operator=(const Director& copy); //  복사연산자 오버로딩 촉수엄금, 차후 변수가 추가되면 여기에다가도 추가해야 신전환에 복사가 될거임


};