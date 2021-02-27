#include "pch.h"
#include "TrainingDetail.h"
#include "Staff.h"

TrainingDetail::TrainingDetail()
	:UI("TrainingDetail")
{
	mIsActive = false;
}

void TrainingDetail::Init()
{
	LoadFromFile("TrainingDetail");
	IMAGEMANAGER->LoadFromFile((L"TrainingDetail"), Resources(L"TrainingDetail.bmp"), 1280, 719, true);
	mImage = IMAGEMANAGER->FindImage(L"TrainingDetail");

	trainingRect[0] = RectMake(1116, 248, 16, 18);
	trainingRect[1] = RectMake(1116 + 18, 248, 16, 18);
	trainingRect[2] = RectMake(1116 + 18 + 18, 248, 16, 18);
}

void TrainingDetail::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
		RenderStaffInfo(hdc);
		MouseOver(hdc);

	}

}

void TrainingDetail::Update()
{
	if (mIsActive)
	{

		Staff* tmp=(Staff*)Storage::GetInstance()->FindObject(mCurrentStaff->GetName());
		
		originAtk = tmp->GetAtk();
		originDef = tmp->GetDef();
		originPoint = tmp->GetTrainingPoint();

		function <void(void)> func = [this]() 
		{
			if (originAtk < mCurrentStaff->GetAtk())
			{
				mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusAtk();
			}
			
		};
		mToggleButton(0, "None", func);

		func = [this] ()
		{
			if (mCurrentStaff->GetTrainingPoint() > 0)
			{
				mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusAtk();
			}
		};
		mToggleButton(1, "None", func);

		func = [this]()
		{
			if (originDef < mCurrentStaff->GetDef())
			{
				mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusDef();
			}
		};
		mToggleButton(2, "None", func);

		func = [this]()
		{
			if (mCurrentStaff->GetTrainingPoint() > 0)
			{
				mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusDef();
			}
		};
		mToggleButton(3, "None", func);

		




	}


}

void TrainingDetail::Release()
{
}

void TrainingDetail::SetStaff(Staff * currentStaff)
{
	mCurrentStaff = currentStaff;
}

void TrainingDetail::RenderStaffInfo(HDC hdc)
{
	auto caching = mCurrentStaff->GetMostChamp();

	string mostChamp1 = caching.begin()->first;
	string mostChamp2 = (caching.begin()++)->first;

	//설정 중인 선수 숙련픽 1 표시
	wstring tmp1; 
	tmp1.assign(mostChamp1.begin(), mostChamp1.end());
	TextOut(hdc, 542, 386, tmp1.c_str(), tmp1.size());
	
	//설정 중인 선수 숙련픽 2 표시
	wstring tmp2;
	tmp2.assign(mostChamp2.begin(), mostChamp2.end());
	TextOut(hdc, 924, 386, tmp2.c_str(), tmp2.size());

	//설정 중인 선수 공격력 표시
	int atk = mCurrentStaff->GetAtk();
	wstring tmp3 = to_wstring(atk);
	TextOut(hdc, 747, 307, tmp3.c_str(), tmp3.size());
	
	//설정 중인 선수 방어력 표시
	int def = mCurrentStaff->GetDef();
	wstring tmp4 = to_wstring(def);
	TextOut(hdc, 1115, 307, tmp4.c_str(), tmp4.size());

	//훈련 포인트 드로잉 노란 박스
	HBRUSH newB = CreateSolidBrush(RGB(255, 189, 33));
	HBRUSH oldB = (HBRUSH)SelectObject(hdc, newB);
	switch (mCurrentStaff->GetTrainingPoint())
	{
	case 0 :
		break;

	case 1:
		RenderRect(hdc, trainingRect[0]);
		break;

	case 2:
		RenderRect(hdc, trainingRect[0]);
		RenderRect(hdc, trainingRect[1]);
		break;

	case 3:
		RenderRect(hdc, trainingRect[0]);
		RenderRect(hdc, trainingRect[1]);
		RenderRect(hdc, trainingRect[2]);
		break;
	}
	SelectObject(hdc, oldB);
	DeleteObject(newB);

}