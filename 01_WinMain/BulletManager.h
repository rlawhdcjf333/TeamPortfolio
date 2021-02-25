#pragma once
#include "Animation.h"
class BulletManager
{
private:
	float mX;
	float mY;
	float mEndX;
	float mEndY;

	float mAngle;
	float mSpeed;

	RECT mRect;

	void Init(float startX, float startY, float endX, float endY);
	void Release();
	void Update();
	void Render(HDC hdc);
};

