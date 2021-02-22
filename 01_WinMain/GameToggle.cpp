#include "pch.h"
#include "GameToggle.h"
#include "ChampInfo.h"

GameToggle::GameToggle()
	:GameObject("GameToggle")
{
	mIsActive = false;
}

void GameToggle::Init()
{
	RECT champInfo = RectMake(554, 596, 162, 50);
	mButtonList.push_back(champInfo);


	IMAGEMANAGER->LoadFromFile(L"GameToggle", Resources(L"GameToggle.bmp"), 162, 50, true);
	mImage = IMAGEMANAGER->FindImage(L"GameToggle");

	IMAGEMANAGER->LoadFromFile(L"GameToggleClick", Resources(L"GameToggleClick.bmp"), 162, 50, true);
	mActive = IMAGEMANAGER->FindImage(L"GameToggleClick");

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new ChampInfo);

}

void GameToggle::Release()
{
}

void GameToggle::Update()
{
	if (mIsActive)
	{

		auto func = []() {ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false); };
		mToggleButton(0, "ChampInfo", func);


	}

}

void GameToggle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 544, 596);
		mActive->Render(hdc, 544, 648);
	}

}

void GameToggle::mToggleButton(int index, string UIName, function <void(void)> func)
{
	if (PtInRect(&mButtonList[index], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			GameObject* hptr = ObjectManager::GetInstance()->FindObject(UIName);
			hptr->SetIsActive(!hptr->GetIsActive());

			func();

		}
	}
}