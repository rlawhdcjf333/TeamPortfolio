#pragma once
#include "GameObject.h"

class UI : public GameObject
{
	vector <RECT> mButtonList;
	string mFileName;
	Image* mImage;

public:
	UI(const string& name, const string& fileName);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void LoadFromFile(const string& fileName);

	void mSceneChangeButton(int index, wstring nextSceneName);
};

