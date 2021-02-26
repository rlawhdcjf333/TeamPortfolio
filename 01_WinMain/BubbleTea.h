#pragma once
#include "Champ.h"
class BubbleTea : public Champ
{
public:

	BubbleTea(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

