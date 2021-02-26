#pragma once
#include "Champ.h"
class Tank : public Champ
{
public:

	Tank(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
