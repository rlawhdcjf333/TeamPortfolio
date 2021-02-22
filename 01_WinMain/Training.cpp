#include "pch.h"
#include "Training.h"

Training::Training()
	:UI("Training")
{
	mIsActive = false;
}

void Training::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Training", Resources(L"Training.bmp"), 1247, 557,true);
	mImage = IMAGEMANAGER->FindImage(L"Training");
}

void Training::Release()
{
}

void Training::Update()
{
}

void Training::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 17, 53);
	}


}
