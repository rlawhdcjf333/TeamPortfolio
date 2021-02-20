#pragma once
#include "GameObject.h"
class Animation;
class Champ : public GameObject
{
	Image* mImage;

	Animation* mCurrentAnm;
	float mAlpha;
public:
	Champ(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};