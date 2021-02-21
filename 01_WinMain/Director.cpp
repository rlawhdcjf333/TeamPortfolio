#include "pch.h"
#include "Director.h"
#include "Staff.h"

Director::Director(const string& name, const wstring& fileName)
	:GameObject(name)
{
	mFileName = fileName;
}

// 열정만수르, joy room, 김복남소머리국밥
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