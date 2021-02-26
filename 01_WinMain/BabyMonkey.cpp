#include "pch.h"
#include "BabyMonkey.h"
#include "Animation.h"

BabyMonkey::BabyMonkey(const string& name )
	:Champ(name) 
{
	mChampName = L"BabyMonkey";
	mClassType = ClassType::Supporter;
}

void BabyMonkey::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"BabyMonkey", Resources(L"BabyMonkey.bmp"), 480, 600, 6, 10, true);
	mImage = IMAGEMANAGER->FindImage(L"BabyMonkey");
}

void BabyMonkey::Release()
{

}

void BabyMonkey::Update()
{

}

void BabyMonkey::Render(HDC hdc)
{

}

