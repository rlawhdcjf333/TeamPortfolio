#pragma once
#include "Champ.h"
class MistKnight : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	MistKnight();
	MistKnight(string str, float  x, float y);
	MistKnight(string str);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

