#include "pch.h"
#include "Background.h"
#include "Image.h"

Background::Background(const string& name, const wstring& fileName)

	: GameObject(name) 
{
	mFileName = fileName;
}

void Background::Init()
{
	IMAGEMANAGER->LoadFromFile(mFileName, Resources(mFileName+L".bmp"),1280,720, false);
	mImage = IMAGEMANAGER->FindImage(mFileName);

	if (mFileName == L"Title")
	{
		IMAGEMANAGER->LoadFromFile(L"TitleClearBuffer", Resources(L"TitleClearBuffer.bmp"), 1280, 720, false);
	}

}

void Background::Release()
{
}

void Background::Update()
{
}

void Background::Render(HDC hdc)
{
	mImage->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);
}
