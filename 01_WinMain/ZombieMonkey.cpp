#include "pch.h"
#include "ZombieMonkey.h"
#include "Animation.h"

ZombieMonkey::ZombieMonkey(const string& name)
	:Champ(name) 
{
	mChampName = L"ZombieMonkey";
	mClassType = ClassType::Supporter;
}

void ZombieMonkey::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"ZombieMonkey", Resources(L"ZombieMonkey.bmp"), 2210, 2040, 13, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"ZombieMonkey");
}

void ZombieMonkey::Release()
{

}

void ZombieMonkey::Update()
{

}

void ZombieMonkey::Render(HDC hdc)
{

}

