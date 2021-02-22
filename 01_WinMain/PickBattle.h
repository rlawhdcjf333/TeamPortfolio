#pragma once
#include "Scene.h"
class PickBattle : public Scene
{
	int EventCount;

	int mLevel;		//단계 제어 변수
	bool mLevelEnd;	//단계 변경 변수

	//1단계 : 선수 선발 + 상대팀 표시
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

