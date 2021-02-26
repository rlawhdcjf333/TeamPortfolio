#include "pch.h"
#include "StaffSearch.h"
#include  "StaffResult.h"
#include "Director.h"
#include "Staff.h"
#include "StaffList.h"
#include "Training.h"

StaffResult::StaffResult(int x, int y, Director* dir)
	:UI("StaffResult")
{
	mIsActive = false;
	mX = x;
	mY = y;
	mDirector = dir;

	StaffList* tmp1 = (StaffList*)ObjectManager::GetInstance()->FindObject("StaffList");
	mStaffList = tmp1;

	Training* tmp2 = (Training*)ObjectManager::GetInstance()->FindObject("Training");
	mTraining = tmp2;

}

void StaffResult::Init()
{
	RECT rc1 = RectMake(mX + 18, mY + 331, 118, 30);
	mButtonList.push_back(rc1);
	RECT rc2 = RectMake(mX + 158, mY + 331, 118, 30);
	mButtonList.push_back(rc2);

	IMAGEMANAGER->LoadFromFile(L"StaffResult", Resources(L"StaffResult.bmp"), 293, 381, true);
	mImage = IMAGEMANAGER->FindImage(L"StaffResult");

	string newStaffName = mDirector->RandomName();
	mStaff = new Staff(newStaffName, newStaffName, L"TeamNuguri");
	mStaff->Init();
	mStaff->SetTrainingPoint(0); //���� �����ϴ� ������ �Ʒ�����Ʈ 0���� �ʱ�ȭ

	mCost = 100 + mStaff->GetAtk() * 10 + mStaff->GetDef() * 10;

}

void StaffResult::Release()
{
	if (mStaff != nullptr)
	{
		mStaff->Release();
		SafeDelete(mStaff);
	}
}

void StaffResult::Update()
{
	if (mIsActive)
	{

		function<void(void)> func = [this]()
		{
			if (mDirector->GetGold() >= mCost and mDirector->GetStaffNameList().size() <5) 
			{
				mDirector->SetGold(mDirector->GetGold() - mCost); //��� ���ְ�
				
				Staff* copy = new Staff(*mStaff); // ������ ������ ����
				ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, copy); // �Ŵ������� ���
				Storage::GetInstance()->StaffInsert(copy);// ����ҿ��� ���
				mDirector->AddStaff(copy->GetName()); // ���� ���
				mStaffList->UpdateStaffList(); //������ ui ������Ʈ
				mTraining->UpdateStaffList();  // �Ʒ� ui ������Ʈ


				mStaff->Release(); // ������� �����
				SafeDelete(mStaff);

				mIsActive = false;
			}
		};
		mToggleButton(0, "None", func); //�����ϱ�
		
		if (!mIsActive) return; // ���Ѿ�� �����ְ�

		func = [this]()
		{
			mStaff->Release(); // ������� �����
			SafeDelete(mStaff);

			mIsActive = false;
		};
		mToggleButton(1, "None", func); //�����ϱ�


	}


}

void StaffResult::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, mX, mY);
		MouseOver(hdc);
		
		//�� ǥ��
		mStaff->UIRender(hdc, mX + 14, mY + 8, 48, 48);
		
		//�̸� ǥ��
		string tmpName = mStaff->GetStaffName();
		wstring nameStr;
		nameStr.assign(tmpName.begin(), tmpName.end());
		TextOut(hdc, mX+80, mY+12, nameStr.c_str(), nameStr.size());

		//���ݷ� ǥ��
		int tmpAtk = mStaff->GetAtk();
		wstring atkStr = to_wstring(tmpAtk);
		TextOut(hdc, mX+105, mY+40, atkStr.c_str(), atkStr.size());

		//���� ǥ��
		int tmpDef = mStaff->GetDef();
		wstring defStr = to_wstring(tmpDef);
		TextOut(hdc, mX+190, mY+40, defStr.c_str(), defStr.size());

		//Ư�� ǥ��
		wstring tmpChar = mStaff->GetCharComment(1);
		TextOut(hdc, mX+35, mY+150, tmpChar.c_str(), tmpChar.size());

		//Ư�� ���� ǥ��
		wstring tmpCharInfo = mStaff->GetCharInfo(1);
		TextOut(hdc, mX + 35, mY + 170, tmpCharInfo.c_str(), tmpCharInfo.size());

		//��� ǥ��
		RECT tmpRect = RectMake(mX + 150, mY + 272, 90, 38);
		wstring costStr = to_wstring(mCost);
		DrawText(hdc, costStr.c_str(), costStr.size(), &tmpRect, DT_SINGLELINE | DT_VCENTER | DT_RIGHT);

	}

}