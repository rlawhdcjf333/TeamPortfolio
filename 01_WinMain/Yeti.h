#pragma once
#include "Champ.h"
class Yeti : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	Yeti();
	Yeti(string str, float  x, float y);
	Yeti(const string name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

