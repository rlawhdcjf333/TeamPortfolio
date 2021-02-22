#pragma once
#include "GameObject.h"

// ���� ����Ʈ
class Staff;
class Director : public GameObject
{
	vector<string> mNameList;

	Image* mTeamImage;
	wstring mFileName;

	//vector<Image*> mTeamList;
	//map<wstring, Staff*> mStaffList;
public:
	Director(const string& name, const wstring& fileName);

	string RandomName();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};