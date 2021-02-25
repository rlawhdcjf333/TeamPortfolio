#include "pch.h"
#include "OperationToggle.h"

OperationToggle::OperationToggle()
	:UI("OperationToggle")
{
	mIsActive = false;
}

void OperationToggle::Init()
{
	LoadFromFile("OperationToggle");

	IMAGEMANAGER->LoadFromFile(L"OperationToggle", Resources(L"OperationToggle.bmp"), 162, 194, true);
	mImage = IMAGEMANAGER->FindImage(L"OperationToggle");

	IMAGEMANAGER->LoadFromFile(L"OperationToggleClick", Resources(L"OperationToggleClick.bmp"), 162, 50, true);
	mActive = IMAGEMANAGER->FindImage(L"OperationToggleClick");



}

void OperationToggle::Release()
{
}

void OperationToggle::Update()
{
	if (mIsActive)
	{


		auto func = [] () {ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false); };
		mToggleButton(1, "OnPatch", func);
		mToggleButton(2, "OnPatch", func);


	}

}

void OperationToggle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 193, 454);
		MouseOver(hdc);
		mActive->Render(hdc, 191, 648);
	}

}
