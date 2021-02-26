#pragma once
#include "UI.h"

class News :public UI
{
	Image* mImage;
	wstring* mNews;

public:

	News();
	void Init() override;
	void Render(HDC hdc) override;
	void Release() override;
	void Update() override;
};