#pragma once
#include "GameObject.h"

// ���� ����Ʈ
class Staff;
class Director : public GameObject
{
	vector<string> mRandomNameList; //GameObject�� �ڵ��ϴ� mName ������ �򰥸��ϴ�. �̸� �ٲټ��� -CTO

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
};