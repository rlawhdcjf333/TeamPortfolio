#pragma once
#include "Scene.h"
using namespace std;

class PickBattle : public Scene
{
	int EventCount;

	int mLevel;		//�ܰ� ���� ����
	bool mLevelEnd;	//�ܰ� ���� ����
	function<void(void)> func;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Update1();
	void Update2();
	void Update3();
	void Update4();

	void Render1();
	void Render2();
	void Render3();
	void Render4();
};

