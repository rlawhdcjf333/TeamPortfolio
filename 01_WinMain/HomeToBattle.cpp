#include "pch.h"
#include "HomeToBattle.h"
#include "Director.h"


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

				Director* player = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
				int thisWeek = player->GetWeek();
				if (thisWeek == 3)
				{
					if (player->GetRank() >2)
					{
						MessageBox(_hWnd, L"플레이오프 진출에 실패했다...너구리는 눈앞이 캄캄해졌다...", L"감독님 죄송해요", MB_OK);
						player->SetWeek(1);
						SceneManager::GetInstance()->LoadScene(L"Title");
					}
				}

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


