#include "pch.h"
#include "Peedback.h"

Peedback::Peedback() : UI("Peedback")
{
	mIsActive = false;
}

void Peedback::Init()
{
	LoadFromFile("Peedback");
	IMAGEMANAGER->LoadFromFile(L"Peedback", Resources(L"peedback.bmp"), 1252, 204, true);
	mImage = IMAGEMANAGER->FindImage(L"Peedback");
}

void Peedback::Release()
{
}

void Peedback::Update()
{
	if (!mIsActive)
		return;
	/*
		1	2
		3	4
	*/
	mToggleButton(1, "Peedback", []() {
		/*�ǵ�� 1�� ��ư ������ �۵��� �ڵ�*/
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
	mToggleButton(2, "Peedback", []() {
		/*�ǵ�� 2�� ��ư ������ �۵��� �ڵ�*/
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
	mToggleButton(3, "Peedback", []() {
		/*�ǵ�� 3�� ��ư ������ �۵��� �ڵ�*/
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
	mToggleButton(4, "Peedback", []() {
		/*�ǵ�� 4�� ��ư ������ �۵��� �ڵ�*/
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
}

void Peedback::Render(HDC hdc)
{
	if (mIsActive)
		mImage->Render(hdc, mButtonList[0].left, mButtonList[0].top);
}
