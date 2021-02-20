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
	IMAGEMANAGER->LoadFromFile(mFileName, Resources(mFileName+L".bmp"), 936, 624, false);
	mImage = IMAGEMANAGER->FindImage(mFileName);

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
