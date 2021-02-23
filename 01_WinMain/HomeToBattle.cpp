#include "pch.h"
#include "HomeToBattle.h"


HomeToBattle::HomeToBattle()
	:UI("HomeToBattle")
{
	mIsActive = false;
}

void HomeToBattle::Init()
{
	LoadFromFile("HomeToBattle");

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
		if (PtInRect(&mButtonList[0], _mousePosition)) {

			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

				SceneManager::GetInstance()->LoadScene(L"PickBattle");
				return;
			}
		}

		mToggleButton(1, "HomeToBattle");
	}


}

void HomeToBattle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 463, 245);
		MouseOver(hdc);

	}

}


