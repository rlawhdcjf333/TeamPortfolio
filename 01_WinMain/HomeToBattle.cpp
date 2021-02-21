#include "pch.h"
#include "HomeToBattle.h"

HomeToBattle::HomeToBattle()
	:GameObject("HomeToBattle")
{
	mIsActive = false;
}

void HomeToBattle::Init()
{
	IMAGEMANAGER->LoadFromFile(L"HomeToBattle", Resources(L"HomeToBattle.bmp"), 353, 229, true);
	mImage = IMAGEMANAGER->FindImage(L"HomeToBattle");
}

void HomeToBattle::Release()
{
}

void HomeToBattle::Update()
{
	if (mIsActive)
	{



	}

}

void HomeToBattle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 463, 245);

	}

}
