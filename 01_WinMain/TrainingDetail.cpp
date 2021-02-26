#include "pch.h"
#include "TrainingDetail.h"
#include "Staff.h"
#include "Champ.h"

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
		//만일 3이 아니라 변수로 이 값을 대체하면 시설 개선을 구현할 수 있다.

		function <void(void)> func = [this]() 
		{
			mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusAtk();
			if (mCurrentStaff->GetTrainingPoint() > 3 or mCurrentStaff->GetAtk()<1)
			{
				mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusAtk();
			}
			
		};
		mToggleButton(0, "None", func);

		func = [this] ()
		{
			mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusAtk();
			if (mCurrentStaff->GetTrainingPoint() < 0)
			{
				mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusAtk();
			}
		};
		mToggleButton(1, "None", func);

		func = [this]()
		{
			mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusDef();
			if (mCurrentStaff->GetTrainingPoint() > 3 or mCurrentStaff->GetDef()<1)
			{
				mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusDef();
			}
		};
		mToggleButton(2, "None", func);

		func = [this]()
		{
			mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusDef();
			if (mCurrentStaff->GetTrainingPoint() < 0)
			{
				mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusDef();
			}
		};
		mToggleButton(3, "None", func);

		func = [this]()
		{
			mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusMost1();
			if (mCurrentStaff->GetTrainingPoint() > 3 or mCurrentStaff->GetMostChamp().begin()->second < 1)
			{
				mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusMost1();
			}

		};
		mToggleButton(4, "None", func);

		func = [this]()
		{
			mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusMost1();
			if (mCurrentStaff->GetTrainingPoint() < 0)
			{
				mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusMost1();
			}

		};
		mToggleButton(5, "None", func);

		func = [this]()
		{
			mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusMost2();
			if (mCurrentStaff->GetTrainingPoint() > 3 or mCurrentStaff->GetMostChamp().rbegin()->second<1)
			{
				mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusMost2();
			}

		};
		mToggleButton(6, "None", func);

		func = [this]()
		{
			mCurrentStaff->MinusTrainingPoint(); mCurrentStaff->PlusMost2();
			if (mCurrentStaff->GetTrainingPoint() < 0)
			{
				mCurrentStaff->PlusTrainingPoint(); mCurrentStaff->MinusMost2();
			}

		};
		mToggleButton(7, "None", func);


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
	auto list = mCurrentStaff->GetMostChamp();

	Champ* mostChamp1 = (Champ*)ObjectManager::GetInstance()->FindObject(list.begin()->first);
	Champ* mostChamp2 = (Champ*)ObjectManager::GetInstance()->FindObject(list.rbegin()->first);

	//설정 중인 선수 숙련픽 1 표시
	wstring tmp1 = mostChamp1->GetChampName();
	mostChamp1->UIRender(hdc, 485, 368, 48, 48);
	TextOut(hdc, 542, 386, tmp1.c_str(), tmp1.size());

	//숙련픽 1 숙련도
	wstring mostPt1 = to_wstring(list.begin()->second);
	TextOut(hdc, 747, 382, mostPt1.c_str(), mostPt1.size());

	//설정 중인 선수 숙련픽 2 표시
	wstring tmp2 = mostChamp2->GetChampName();
	mostChamp2->UIRender(hdc, 868, 368, 48, 48);
	TextOut(hdc, 924, 386, tmp2.c_str(), tmp2.size());

	//숙련픽 2 숙련도
	wstring mostPt2 = to_wstring(list.rbegin()->second);
	TextOut(hdc, 1115, 382, mostPt2.c_str(), mostPt2.size());

	//설정 중인 선수 이름 표시
	wstring name = StoW(mCurrentStaff->GetStaffName());
	RECT nameRect = { 510, 244, 600, 268 };
	DrawText(hdc, name.c_str(), name.size(), &nameRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE |DT_END_ELLIPSIS|DT_MODIFYSTRING);

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