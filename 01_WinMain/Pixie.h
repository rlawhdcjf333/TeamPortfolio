#pragma once
#include "Champ.h"
class Pixie : public Champ
{
	typedef map<wstring, Animation*> ::iterator iter;
	iter mapIter;
	Image* mMagicCircle;
public:

	Pixie();
	Pixie(const string& name);
	Pixie(string str, float  x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};