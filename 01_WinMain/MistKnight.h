#pragma once
#include "Champ.h"
class MistKnight : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	MistKnight();
	MistKnight(const string& name);
	MistKnight(string str, float  x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

