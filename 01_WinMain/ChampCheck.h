#pragma once
#include "UI.h"

class ChampCheck : public UI
{
	Image* mImage;
	bool mIsClick;

	Champ* mFirst;
	Champ* mSecond;
public:
	ChampCheck();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void ChampRender(HDC hdc, int x, int y, Champ* champ);

	void ConfirmChamp();

};

