#include "pch.h"
#include "Director.h"
#include "Staff.h"

Director::Director(const string& name, const wstring& fileName)
	:GameObject(name)
{
	mFileName = fileName;
}

// 굳이 감독 캐릭터가 필요할까??
// 팀이름
// TeamMansu, TeamJoyRoom, TeamCowHead
void Director::Init()
{
	LoadFromFile(mFileName);
}

void Director::Release()
{
	SafeDelete(mTeamImage);
}

void Director::Update()
{

}

void Director::Render(HDC hdc)
{
	//mTeamImage->Redner();
}

void Director::LoadFromFile(const wstring& fileName)
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(fileName, Resources(fileName + L".bmp"), 60, 60, true);
	mTeamImage = IMAGEMANAGER->GetInstance()->FindImage(fileName);
}