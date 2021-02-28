#include "pch.h"
#include "ChampCheck.h"
#include "Champ.h"
#include "Staff.h"

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

	mFirst = nullptr;
	mSecond = nullptr;
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
		SoundPlayer::GetInstance()->AllPause();
		SoundPlayer::GetInstance()->Play(L"Airman", 0.2f);
	}
	mToggleButton(0, "ChampCheck", []() {	//¹èÆ²UIÈ°¼º
		ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(false); 
		ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(true);
		SoundPlayer::GetInstance()->AllPause();
		SoundPlayer::GetInstance()->Play(L"Airman", 0.2f);
	});

	// mButtonList[1~3] : BlueÆÀ,  mButtonList[4~6] : RedÆÀ
	if (BData->GetPlayerTeam() == Team::Blue)
	{
		mToggleButton(1, "None", [this]() {	//Blue 1¹ø Ã¨ÇÁ
			if (!mFirst)
				mFirst = BData->GetSelectChamp(Team::Blue, 0);
			else
				mSecond = BData->GetSelectChamp(Team::Blue, 0);
		});
		mToggleButton(2, "None", [this]() {	//Blue 2¹ø Ã¨ÇÁ
			if (!mFirst)
				mFirst = BData->GetSelectChamp(Team::Blue, 1);
			else
				mSecond = BData->GetSelectChamp(Team::Blue, 1);
		});
		mToggleButton(3, "None", [this]() {	//Blue 3¹ø Ã¨ÇÁ
			if (!mFirst)
				mFirst = BData->GetSelectChamp(Team::Blue, 2);
			else
				mSecond = BData->GetSelectChamp(Team::Blue, 2);
		});
	}

	if (BData->GetPlayerTeam() == Team::Red)
	{
		mToggleButton(4, "None", [this]() {	//Blue 1¹ø Ã¨ÇÁ
			if (!mFirst)
				mFirst = BData->GetSelectChamp(Team::Red, 0);
			else
				mSecond = BData->GetSelectChamp(Team::Red, 0);
		});
		mToggleButton(5, "None", [this]() {	//Blue 2¹ø Ã¨ÇÁ
			if (!mFirst)
				mFirst = BData->GetSelectChamp(Team::Red, 1);
			else
				mSecond = BData->GetSelectChamp(Team::Red, 1);
		});
		mToggleButton(6, "None", [this]() {	//Blue 3¹ø Ã¨ÇÁ
			if (!mFirst)
				mFirst = BData->GetSelectChamp(Team::Red, 2);
			else
				mSecond = BData->GetSelectChamp(Team::Red, 2);
		});
	}

	if (mFirst && mSecond)
	{
		BData->ChampSwap(mFirst, mSecond);
		mFirst = nullptr;
		mSecond = nullptr;
	}
}

void ChampCheck::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);

		//BlueÆÀ
		ChampRender(hdc, mButtonList[1].left, mButtonList[1].top + 30, BData->GetSelectChamp(Team::Blue, 0));
		ChampRender(hdc, mButtonList[2].left, mButtonList[2].top + 30, BData->GetSelectChamp(Team::Blue, 1));
		ChampRender(hdc, mButtonList[3].left, mButtonList[3].top + 30, BData->GetSelectChamp(Team::Blue, 2));
		//RedÆÀ
		ChampRender(hdc, mButtonList[4].left, mButtonList[4].top + 30, BData->GetSelectChamp(Team::Red, 0));
		ChampRender(hdc, mButtonList[5].left, mButtonList[5].top + 30, BData->GetSelectChamp(Team::Red, 1));
		ChampRender(hdc, mButtonList[6].left, mButtonList[6].top + 30, BData->GetSelectChamp(Team::Red, 2));

		MouseOver(hdc);
	}
}

void ChampCheck::ChampRender(HDC hdc, int x, int y, Champ* champ)
{
	if (!champ)
		return;
	champ->UIRender(hdc, x + 20, y, 70, 70);

	wstring champName = champ->GetChampName();
	RECT nameBox = RectMake(x + 20, y + 90, 77, 30);
	CallFont(hdc, 12, [hdc, champName, &nameBox]() {DrawText(hdc, champName.c_str(), champName.size(), &nameBox, DT_SINGLELINE | DT_VCENTER | DT_CENTER); });
}

void ChampCheck::ConfirmChamp()
{
	vector <Champ*> myTeam;
	vector <Champ*> enemyTeam;

	switch (BData->GetPlayerTeam())
	{
		case Team::Red:
			myTeam = BData->GetSelectChampList(Team::Red);
			enemyTeam = BData->GetSelectChampList(Team::Blue);
			break;
		case Team::Blue:
			myTeam = BData->GetSelectChampList(Team::Red);
			enemyTeam = BData->GetSelectChampList(Team::Blue);
			break;
	}
	
	



}



