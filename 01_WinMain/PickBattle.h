#pragma once
#include "Scene.h"
class PickBattle : public Scene
{
	int EventCount;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Zorder();
};

