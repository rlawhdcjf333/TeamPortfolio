#pragma once
#include "UI.h"

class System : public UI{
	Image* mImage;
	
	vector<RECT> mRectList;
	HDC mHdc;

	wstring mBackVolumeStr;
	wstring mAllVoulumeStr;
	wstring mSubVoulumeStr;

	float mBackVolume;
	float mAllVolume;
	float mSubVolume;
public:

	System();
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};