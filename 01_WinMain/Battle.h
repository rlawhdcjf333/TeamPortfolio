#pragma once
#include "UI.h"

class Champ;
class Battle : public UI
{
	Image* mImage;
	Image* mUI;
	int Count;	//юс╫ц

	vector<Champ*> mMyTeam;
	vector<Champ*> mEnemyTeam;


public:
	Battle();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

