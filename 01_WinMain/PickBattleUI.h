#pragma once
#include "pch.h"
class PickBanRect {
	//static vector<RECT>Level1Rect;
	//static vector<RECT>Level2Rect;
	//static vector<RECT>Level3Rect;
	//static vector<RECT>Level4Rect;

};
//������ �ܼ��� Static���� �ϸ� �̰� ���� �����͸� �ν��ϴ����� �𸣰�?
static vector<RECT>Level1Rect;
static vector<RECT>Level2Rect;
static vector<RECT>Level3Rect;
static vector<RECT>Level4Rect;
static int mLevel;

class PickBattleUI {
	friend class UI;
	vector<class Staff*>mSelectStaff;
	vector<class Staff*>mEnemyStaff;
public:
	void GetMyStaff() {}
};