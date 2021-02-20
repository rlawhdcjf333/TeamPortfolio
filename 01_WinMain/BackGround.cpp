#include "pch.h"
#include "Background.h"
#include "Image.h"

Background::Background(const string& name, float x, float y)

	: GameObject(name) 
{
	mX = x, mY = y;
}

void Background::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BackGround", Resources(L"Title.bmp"), 936, 624, false);
	mImage = IMAGEMANAGER->FindImage(L"BackGround");

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
