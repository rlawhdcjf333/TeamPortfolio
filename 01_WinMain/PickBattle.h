#pragma once
#include "Scene.h"
class PickBattle : public Scene
{
	int EventCount;

	int mLevel;		//�ܰ� ���� ����
	bool mLevelEnd;	//�ܰ� ���� ����

	//1�ܰ� : ���� ���� + ����� ǥ��
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

