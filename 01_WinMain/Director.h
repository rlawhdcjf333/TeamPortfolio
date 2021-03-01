#pragma once
#include "GameObject.h"

// ���� ����Ʈ
class Staff;
class Director : public GameObject
{
	vector<string> mRandomNameList; 

	Image* mTeamImage;
	wstring mFileName;
	wstring mTeamName;

	int mRound; //3�� 2�� ����
	int mMonth;
	int mWeek;
	int mGold;

	int mRank; //����
	int mWin; // �� �¸� ����
	int mLose; // �� �й� ����
	int mLeagueScore; //�� ����

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
	void PlusWeek() { mWeek++; }
	void SetGold(int gold) { mGold = gold; }

	int GetRound() { return mRound; }
	int GetMonth() { return mMonth; }
	int GetWeek() { return mWeek; }
	int GetGold() { return mGold; }

	void UIRender(HDC hdc, int startX, int startY, int width, int height, bool b = true);
	void TeamImageRender(HDC hdc, int startX, int startY, int widht, int height);
	void TeamImageRender(HDC hdc, RECT rc);

	wstring GetTeamName() { return mTeamName; }

	void SetRank(int rank) { mRank = rank; }
	void SetWin(int win) { mWin = win; }
	void PlusWin() { mWin++; }
	void SetLose(int lose) { mLose = lose; }
	void PlusLose() { mLose++; };
	void SetLeagueScore(int leagueScore) { mLeagueScore = leagueScore; }
	void CalLeagueScore() { mLeagueScore = mWin * 3 + mLose * 1; }
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
	void PopStaff(string name);

public:
	Director(const Director& copy); //���� ������ �����ε�, ���丮�� ��
	Director& operator=(const Director& copy); //  ���翬���� �����ε� �˼�����, ���� ������ �߰��Ǹ� ���⿡�ٰ��� �߰��ؾ� ����ȯ�� ���簡 �ɰ���


};