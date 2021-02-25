#pragma once
#include "UI.h"

class Battle : public UI
{
	Image* mImage;
	Image* mUI;
	int Count;	//юс╫ц
public:
	Battle();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

