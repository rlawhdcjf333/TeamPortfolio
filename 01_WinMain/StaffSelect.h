#pragma once
#include "UI.h"

class Director;
class StaffSelect : public UI
{
	Image* mImage;

	Director* player;
	Director* enemy;

	int startX;
	int startY;

public:
	StaffSelect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetImage(Image* img) { mImage = img; } //이걸 씬 init에서 쓰면~~
};

