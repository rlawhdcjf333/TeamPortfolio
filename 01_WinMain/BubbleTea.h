#pragma once
#include "Champ.h"
class BubbleTea : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

	bool mIsMode;
	float mModeTime;
	float mRangeBuff;
	float mInitRange;
public:

	BubbleTea();
	BubbleTea(string str, float  x, float y);
	BubbleTea(string str);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Mode(float time, float plusrange, float plusdamage);

};