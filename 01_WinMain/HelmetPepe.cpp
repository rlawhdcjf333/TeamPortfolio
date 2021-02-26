#include "pch.h"
#include "HelmetPepe.h"

HelmetPepe::HelmetPepe(const string& name)
	:Champ(name) 
{
	mChampName = L"HelmetPepe";
	mClassType = ClassType::Warrior;
}

void HelmetPepe::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"HelmetPepe", Resources(L"HelmetPepe.bmp"), 1040, 1440, 8, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"HelmetPepe");
}

void HelmetPepe::Release()
{
}

void HelmetPepe::Update()
{
}

void HelmetPepe::Render(HDC hdc)
{
}
