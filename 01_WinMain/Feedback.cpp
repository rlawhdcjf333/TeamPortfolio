#include "pch.h"
#include "Feedback.h"

Feedback::Feedback() : UI("Feedback")
{
	mIsActive = false;
}

void Feedback::Init()
{
	LoadFromFile("Feedback");
	IMAGEMANAGER->LoadFromFile(L"Feedback", Resources(L"peedback.bmp"), 1252, 204, true);
	mImage = IMAGEMANAGER->FindImage(L"Feedback");
}

void Feedback::Release()
{
}

void Feedback::Update()
{
	if (!mIsActive)
		return;
	/*
		1	2
		3	4
	*/
	mToggleButton(1, "Feedback", []() {
		/*�ǵ�� 1�� ��ư ������ �۵��� �ڵ�*/
		BData->Feedback(1);
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
	mToggleButton(2, "Feedback", []() {
		/*�ǵ�� 2�� ��ư ������ �۵��� �ڵ�*/
		BData->Feedback(2);
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
	mToggleButton(3, "Feedback", []() {
		/*�ǵ�� 3�� ��ư ������ �۵��� �ڵ�*/
		BData->Feedback(3);
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
	mToggleButton(4, "Feedback", []() {
		/*�ǵ�� 4�� ��ư ������ �۵��� �ڵ�*/
		BData->Feedback(4);
		ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		});
}

void Feedback::Render(HDC hdc)
{
	if (mIsActive)
		mImage->Render(hdc, mButtonList[0].left, mButtonList[0].top);
}
