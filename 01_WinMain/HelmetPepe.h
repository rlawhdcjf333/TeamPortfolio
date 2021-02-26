#pragma once
#include "Champ.h"
class HelmetPepe : public Champ
{
public:

	HelmetPepe(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};