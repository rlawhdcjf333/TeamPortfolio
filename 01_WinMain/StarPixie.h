#pragma once
#include "Champ.h"
class StarPixie: public Champ
{
private:
	float mSkillCasting;
	float mTimer;
public:

	StarPixie(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
