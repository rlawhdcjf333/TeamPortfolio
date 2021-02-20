#pragma once
#include "GameObject.h"
#include <functional>


class UI : public GameObject
{
	vector <RECT> mButtonList;
	string mFileName;
	Image* mImage;
	bool mTrigger;


public:
	UI(const string& name, const string& fileName);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void LoadFromFile(const string& fileName);

	void mToggleButton(int index, string UIName);
	void mSceneChangeButton(int index, wstring nextSceneName, bool sceneEvent =false, function <void(void)> func = []() {});

	void homeUIInit();
};

