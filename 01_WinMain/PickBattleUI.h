#pragma once
#include "pch.h"
class PickBanRect {
	//static vector<RECT>Level1Rect;
	//static vector<RECT>Level2Rect;
	//static vector<RECT>Level3Rect;
	//static vector<RECT>Level4Rect;

};
//문제는 단순히 Static으로 하면 이게 같은 포인터를 인식하는지도 모르고, Init할때마다 푸시백 해버린다?
static vector<RECT>Level1Rect;
static vector<RECT>Level2Rect;
static vector<RECT>Level3Rect;
static vector<RECT>Level4Rect;
static int mLevel;