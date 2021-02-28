#include "pch.h"
#include "ChampCheck.h"

ChampCheck::ChampCheck() : UI("ChampCheck")
{
	mIsActive = false;
}

void ChampCheck::Init()
{
	LoadFromFile("ChampCheck");
	IMAGEMANAGER->LoadFromFile(L"ChampCheck", Resources(L"ChampCheck.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"ChampCheck");
	mIsClick = false;
}

void ChampCheck::Release()
{
}

void ChampCheck::Update()
{
	if (!mIsActive)
		return;

	if (Input::GetInstance()->GetKeyDown('F'))
	{

		ObjectManager::GetInstance()->FindObject("ChampCheck")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(true);
	}
	mToggleButton(1, "ChampCheck", []() {	//��ƲUIȰ��
		ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(false); 
		ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(true);
		SoundPlayer::GetInstance()->AllPause();
		SoundPlayer::GetInstance()->Play(L"Warsong", 0.2f);
	});

	// mButtonList[2~4] : Blue��,  mButtonList[5~7] : Red��
	mToggleButton(2, "None", []() {	//Blue 1�� è��
		});
}

void ChampCheck::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
	}
}
