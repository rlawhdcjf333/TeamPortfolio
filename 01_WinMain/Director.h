#pragma once
#include "GameObject.h"

// ���� ����Ʈ
class Staff;
class Director : public GameObject
{
	vector<string> mRandomNameList; //GameObject�� �ڵ��ϴ� mName ������ �򰥸��ϴ�. �̸� �ٲټ��� -CTO

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