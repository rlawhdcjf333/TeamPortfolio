#pragma once
#include "GameObject.h"


class UI : public GameObject
{
protected: vector <RECT> mButtonList;

private:
	string mFileName;
	bool mTrigger;

	bool mMouseOverOn;

public:
	UI(const string& name);
	UI(const string& name, const string& fileName);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	virtual void LoadFromFile(const string& fileName);
	virtual void LoadFromFile(const string& fileName1, const string& fileName2);
	
	virtual void MouseOver(HDC hdc);
	//Scene 전환이 일어나지 않는 버튼 토글;
	virtual void mToggleButton(int index, string UIName, function <void(void)> func = []() {});
	//LoadScene 불러오는 버튼 토글; 
	virtual void mSceneChangeButton(int index, wstring nextSceneName, bool sceneEvent =false, function <void(void)> func = []() {});
	
	void TitleUIInit();
	void TitleUIUpdate();

	void homeUIInit();
	void homeUIUpdate();
	void homeUIRender(HDC hdc);

	//PickBattle 제어
	void PickBattleUIInit();
	void PickBattleUIUpdate();

	void SetMouseOver(bool b) { mMouseOverOn = b; }
};

