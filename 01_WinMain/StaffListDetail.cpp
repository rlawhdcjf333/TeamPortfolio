#include "pch.h"
#include "StaffListDetail.h"
#include "StaffList.h"
#include "Training.h"
#include "Staff.h"
#include "Champ.h"
#include "Director.h"

StaffListDetail::StaffListDetail()
	:UI("StaffListDetail")
{
	mIsActive = false;
}

void StaffListDetail::Init()
{
	LoadFromFile("StaffListDetail");

	IMAGEMANAGER->LoadFromFile(L"StaffListDetail", Resources(L"StaffListDetail.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"StaffListDetail");

	mDirector = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	mTraining = (Training*)ObjectManager::GetInstance()->FindObject("Training");

	mIsAlertOn = false;
	mDuration = 1.2f;
}

void StaffListDetail::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);

		//�� ������
		mCurrentStaff->UIRender(hdc, 46, 160, 45, 45);

		//�̸� ������
		wstring tmp0 = StoW(mCurrentStaff->GetStaffName());
		TextOut(hdc, 110, 160, tmp0.c_str(), tmp0.size());

		//���ݷ� ǥ��
		wstring tmp1 = to_wstring(mCurrentStaff->GetAtk());
		TextOut(hdc, 140, 192, tmp1.c_str(), tmp1.size());
		RECT atkRect = { 1164,223, 1228,242 };
		DrawText(hdc, tmp1.c_str(), tmp1.size(), &atkRect, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);

		//���� ǥ��
		wstring tmp2 = to_wstring(mCurrentStaff->GetDef());
		TextOut(hdc, 228, 192, tmp2.c_str(), tmp2.size());
		RECT defRect = { 1164,251, 1228,269 };
		DrawText(hdc, tmp2.c_str(), tmp2.size(), &defRect, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);

		//����� ǥ��
		mCurrentStaff->ConditionRender(hdc, 420, 170, 30, 30);

		auto tmp3 = mCurrentStaff->GetMostChamp();

		//��Ʈ �� ǥ��
		Champ* mostChamp1 = (Champ*)ObjectManager::GetInstance()->FindObject(tmp3.begin()->first);
		Champ* mostChamp2 = (Champ*)ObjectManager::GetInstance()->FindObject(tmp3.rbegin()->first);
		mostChamp1->UIRender(hdc, 42, 288, 45, 45);
		mostChamp2->UIRender(hdc, 42, 344, 45, 45);

		//��Ʈ �� �̸� ǥ��
		wstring champName1 = mostChamp1->GetChampName();
		wstring champName2 = mostChamp2->GetChampName();
		RECT champNameRc1 = { 980,278, 1228, 296 };
		RECT champNameRc2 = { 980, 308, 1228, 324 };
		DrawText(hdc, champName1.c_str(), champName1.size(), &champNameRc1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		DrawText(hdc, champName2.c_str(), champName2.size(), &champNameRc2, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

		//��Ʈ �� ���õ� ǥ��
		wstring mostChamp1Pt = to_wstring(tmp3.begin()->second);
		wstring mostChamp2Pt = to_wstring(tmp3.rbegin()->second);
		TextOut(hdc, 175, 315, mostChamp1Pt.c_str(), mostChamp1Pt.size());
		TextOut(hdc, 175, 375, mostChamp2Pt.c_str(), mostChamp2Pt.size());
		DrawText(hdc, mostChamp1Pt.c_str(), mostChamp1Pt.size(), &champNameRc1, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);
		DrawText(hdc, mostChamp2Pt.c_str(), mostChamp2Pt.size(), &champNameRc2, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

		//���� ��� ǥ��
		wstring reCost = to_wstring(mCurrentStaff->GetCost());
		TextOut(hdc, 390, 308, reCost.c_str(), reCost.size());

		//Ư�� ǥ��
		wstring character1 = mCurrentStaff->GetCharComment(1);
		RECT characterRect1 = RectMake(485, 192, 140, 24);
		DrawText(hdc, character1.c_str(), character1.size(), &characterRect1, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		//Ư�� ���� ǥ��
		wstring characterInfo1 = mCurrentStaff->GetCharInfo(1);
		RECT characterInfoRect1 = RectMake(640, 192, 320, 15);
		DrawText(hdc, characterInfo1.c_str(), characterInfo1.size(), &characterInfoRect1, DT_WORDBREAK);
		




		
		RenderAlert(hdc);
	}
}

void StaffListDetail::Update()
{
	
	function <void(void)> func = [this]() 
	{
		if (mStaffList->GetStaffSize() > 3)
		{
			mCurrentStaff->SetIsDestroy(true); //�Ŵ������� ����
			mDirector->PopStaff(mCurrentStaff->GetStaffName()); // �� ���� ������Ʈ
			mStaffList->UpdateStaffList(); //������ ui ������Ʈ
			mTraining->UpdateStaffList(); //�Ʒ� ui ������Ʈ
			mStaffList->SetIsToggleDetail(false);
			mIsActive = false;
		}
		else
		{
			mIsAlertOn = true;
		}
	};
	mToggleButton(0, "None", func);

	func = [this]()
	{
		mStaffList->SetIsToggleDetail(false);
		mIsActive = false;
	};
	mToggleButton(1, "None", func);


}

void StaffListDetail::Release()
{
}

void StaffListDetail::RenderAlert(HDC hdc)
{
	if (mIsAlertOn)
	{
		mDuration -= Time::GetInstance()->DeltaTime();

		HFONT newF = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		HFONT oldF = (HFONT)SelectObject(hdc, newF);
		SetTextColor(hdc, RGB(255, 0, 0));
		wstring alert = L"���� ������ �ּ� 3���� �ο��� �ʿ��մϴ�";
		RECT alertRect = RectMake(Random::GetInstance()->RandomInt(9, 15), Random::GetInstance()->RandomInt(305, 315), 1253, 70);
		DrawText(hdc, alert.c_str(), alert.size(), &alertRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		SelectObject(hdc, oldF);
		DeleteObject(newF);

		SetTextColor(hdc, RGB(255, 255, 255));

		if (mDuration < 0)
		{
			mDuration = 1.2f;
			mIsAlertOn = false;
		}
	}
}