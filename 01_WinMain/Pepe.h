#pragma once
#include "Champ.h"
class Pepe : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	Pepe();
	Pepe(string str, float  x, float y);
	Pepe(string str);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

