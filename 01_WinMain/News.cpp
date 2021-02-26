#include "pch.h"
#include "News.h"

News::News()
	:UI("News")
{
	mIsActive = false;
}

void News::Init()
{
	mButtonList.push_back({ 1107,542,1248,586 });
	mButtonList.push_back({ 63,161,1212,505 });

	IMAGEMANAGER->LoadFromFile(L"News", Resources(L"News.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"News");
}

void News::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);
		HFONT newF = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0);
		HFONT oldF = (HFONT) SelectObject(hdc, newF);
		if (mNews != nullptr)
		{
			DrawText(hdc, mNews->c_str(), mNews->size(), &mButtonList[1], DT_WORDBREAK);
		}
		else
		{
			wstring defaul = L"새로운 소식이 없습니다.";
			DrawText(hdc, defaul.c_str(), defaul.size(), &mButtonList[1], DT_WORDBREAK);
		}
		SelectObject(hdc, oldF);
		DeleteObject(newF);


	}
}

void News::Release()
{
}

void News::Update()
{
	ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("HomeToBattle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
	ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);

	mToggleButton(0, "News");

}
