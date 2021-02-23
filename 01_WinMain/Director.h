#pragma once
#include "GameObject.h"

// 선수 리스트
class Staff;
class Director : public GameObject
{
	vector<string> mRandomNameList; //GameObject가 핸들하는 mName 변수와 헷갈립니다. 이름 바꾸세요 -CTO

	Image* mTeamImage;
	wstring mFileName;

	vector<string> mStaffNameList;
public:
	Director(const string& name, const wstring& fileName);

	string RandomName();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetStaffNameList(vector<string> staffNameList) { mStaffNameList = staffNameList; }
	vector<string> GetStaffNameList() { return mStaffNameList; }
};