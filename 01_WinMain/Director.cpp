#include "pch.h"
#include "Director.h"
#include "Staff.h"

Director::Director(const string& name, const wstring& fileName)
	:GameObject(name)
{
	mFileName = fileName;
}

// ����������, joy room, �躹���ҸӸ�����
void Director::Init()
{
	LoadFromFile(mFileName);
	mName;
}

void Director::Release()
{
}

void Director::Update()
{
}

void Director::Render(HDC hdc)
{
}

void Director::LoadFromFile(const wstring& fileName)
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(fileName, Resources(fileName + L".bmp"), 60, 60, true);
	mTeamImage = IMAGEMANAGER->GetInstance()->FindImage(fileName);
}