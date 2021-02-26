#include "pch.h"
#include "Cornian.h"
#include "Animation.h"

Cornian::Cornian(const string& name)
	:Champ(name) 
{
	mChampName = L"Cornian";
	mClassType = ClassType::Assassin;
}

void Cornian::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Cornian", Resources(L"Cornian.bmp"), 2380, 2720, 7, 16, true);
	mImage = IMAGEMANAGER->FindImage(L"Cornian");

}

void Cornian::Release()
{

}

void Cornian::Update()
{

}

void Cornian::Render(HDC hdc)
{
	//mImage->AlphaScaleFrameRender();
}

