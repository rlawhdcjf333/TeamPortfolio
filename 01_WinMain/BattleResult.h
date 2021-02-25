#pragma once
#include "UI.h"
class BattleResult : public UI
{
	Image *mImage;
public:
	BattleResult();

	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
};

