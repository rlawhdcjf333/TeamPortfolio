#include "pch.h"
#include "Creators.h"

Creators::Creators(const string& name)
	:UI(name) {}

void Creators::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Creators", Resources(L"Creators.bmp"), 117, 181, true);
	mImage = IMAGEMANAGER->FindImage(L"Creators");
}

void Creators::Update()
{
	if (mIsActive)
	{

	}
}

void Creators::Release()
{
}

void Creators::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 990, 100);
	}
}
