#pragma once
#include "Champ.h"
class StarPixie: public Champ
{
private:
	float mSkillCasting;
	float mTimer;
public:

	StarPixie();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
