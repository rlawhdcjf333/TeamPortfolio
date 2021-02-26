#pragma once
#include "Champ.h"
class Cornian : public Champ
{
public:

	Cornian(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
