#pragma once
#include "Champ.h"
class LoveMonkey : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	LoveMonkey();
	LoveMonkey(const string& name);
	LoveMonkey(string str, float  x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

