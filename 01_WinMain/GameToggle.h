#pragma once
#include "UI.h"

class ChampInfo;
class GameToggle :public UI
{
	Image* mActive;
	Image* mImage;

	ChampInfo* mChampInfo;
public:

	GameToggle();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};
