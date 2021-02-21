#include "pch.h"
#include "Champ.h"
#include "Animation.h"

Champ::Champ(const string& name, float x, float y) : GameObject(name)
{
	mX = x, mY = y;
}

void Champ::Init()
{

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Champ::Release()
{
}

void Champ::Update()
{

	//Champ°¡ ÇÒÀÏ
}

void Champ::Render(HDC hdc)
{
	mImage->AlphaScaleFrameRender(hdc, mRect.left, mRect.top, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), 100,100, mAlpha);

}
