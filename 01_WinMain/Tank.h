#pragma once
#include "Champ.h"
class Tank : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

	bool mIsMode;
	float mModeTime;
	float mRangeBuff;
	float mInitRange;
public:

	Tank();
	Tank(const string& name);
	Tank(string str, float  x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Mode(float time, float plusrange, float plusdamage);

};