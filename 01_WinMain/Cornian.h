#pragma once
#include "Champ.h"
class Cornian : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	Cornian();
	Cornian(const string& name);
	Cornian(string str, float  x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

