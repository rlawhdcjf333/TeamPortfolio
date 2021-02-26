#include "pch.h"
#include "OnPatch.h"

OnPatch::OnPatch(const string& name)
	:UI(name) {}

void OnPatch::Init()
{
	IMAGEMANAGER->LoadFromFile(L"OnPatch", Resources(L"OnPatch.bmp"), 260, 132, true);
	mImage = IMAGEMANAGER->FindImage(L"OnPatch");

	mDuration = 1.f;
	mCurrentTime = 0.f;
}

void OnPatch::Update()
{
	if (mIsActive) {

		mCurrentTime += Time::GetInstance()->DeltaTime();

		if (mCurrentTime >= mDuration)
		{
			mCurrentTime = 0.f;
			mIsActive = false;
		}

		if (Input::GetInstance()->GetKeyUp(VK_ESCAPE))
		{
			mCurrentTime = 0.f;
			mIsActive = false;
		}
	}
	

}

void OnPatch::Release()
{
}

void OnPatch::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->AlphaRender(hdc, WINSIZEX/2-130, WINSIZEY/2-66, (mDuration-mCurrentTime) / mDuration);
	}

}
