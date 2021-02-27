#pragma once
#include "UI.h"

class Champ;
class ChampInformation;
class ChampInfo :public UI
{
	Image* mImage;

	wstring mClassTypeName;
	vector<GameObject*> mChampList;
	vector<RECT> mCurrentRectList;

	ChampInformation* mChampInformation;

public:

	ChampInfo();
	void Release()override;
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;

	void LoadAllChampList();
	void LoadWarriorChampList();
	void LoadADCarryChampList();
	void LoadMagicianChampList();
	void LoadSupporterChampList();
	void LoadAssassinChampList();
	void ClassTypeCheck(int index);

	void AssignFromFile(string fileName);
};
