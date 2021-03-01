#pragma once
#include "UI.h"
class BattleResult : public UI
{
	Image *mImage;
	function<void(void)> func;

public:
	BattleResult();

	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
};

