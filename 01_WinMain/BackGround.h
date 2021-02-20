#pragma once
#include "GameObject.h"

class Background : public GameObject
{
	Image* mImage;

public:
	Background(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};


