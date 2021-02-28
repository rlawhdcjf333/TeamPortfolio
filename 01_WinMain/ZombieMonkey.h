#pragma once
#include "Champ.h"
class ZombieMonkey : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;

public:

	ZombieMonkey();
	ZombieMonkey(string str, float  x, float y);
	ZombieMonkey(string str);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

