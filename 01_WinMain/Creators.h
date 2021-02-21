#pragma once
#include "UI.h"

class Creators : public UI
{
	Image* mImage;
	
public:

	Creators(const string& name);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

};

