#pragma once
#include "Champ.h"
class Cornian : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	Cornian();
	Cornian(string str, float  x, float y);
	Cornian(string str);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

