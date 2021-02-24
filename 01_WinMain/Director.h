#pragma once
#include "GameObject.h"

// 선수 리스트
class Staff;
class Director : public GameObject
{
	vector<string> mRandomNameList; //GameObject가 핸들하는 mName 변수와 헷갈립니다. 이름 바꾸세요 -CTO

	Image* mTeamImage;
	wstring mFileName;
	wstring mTeamName;

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

	void UIRender(HDC hdc, int startX, int startY, int width, int height);
	void TeamImageRender(HDC hdc, int startX, int startY, int widht, int height);

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

	void SetStaffNameList(vector<string> staffNameList) { mStaffNameList = staffNameList; }
	vector<string> GetStaffNameList() { return mStaffNameList; }
};