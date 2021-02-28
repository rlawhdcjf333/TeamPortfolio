#include "pch.h"
#include "System.h"

System::System()
	: UI("System")
{
	mIsActive = false;
}

void System::Init()
{
	IMAGEMANAGER->LoadFromFile(L"System", Resources(L"System.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"System");

	// º¼·ý ¼ýÀÚ
	for (int i = 0; i < 3; i++) {
		mRectList.push_back(RectMake(604, 364 + (i * 36), 48, 20));
	}

	// º¼·ý ¹Ù
	for (int i = 0; i < 3; i++) {
		mRectList.push_back(RectMake(676, 368 + (i * 52), 148, 10));
	}
}

void System::Release()
{

}

void System::Update()
{
	LoadFromFile("System");

	if (mIsActive) {
		auto exit = [this]() {	mIsActive = false; };



		mToggleButton(10, "None", exit);
		mBackVolume = SoundPlayer::GetInstance()->GetVolume(L"Warriors");
	}
}

void System::Render(HDC hdc)
{
	if (mIsActive) {
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);
		
		mHdc = hdc;
		mBackVolumeStr = to_wstring(mBackVolume);

		function<void(void)> BackVoulumeFunc = [this]() { DrawText(mHdc, mBackVolumeStr.c_str(), mBackVolumeStr.length(), &mRectList[0], DT_VCENTER | DT_LEFT | DT_SINGLELINE); };

		CallFont(hdc, 20, BackVoulumeFunc);
	}
}
