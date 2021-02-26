#pragma once
#include "UI.h"

class Champ;
class ChampInfo :public UI
{
	Image* mImage;


	wstring mClassTypeName;
	vector<GameObject*> mChampList;
public:

	ChampInfo();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void LoadAllChampList();
	void LoadWarriorChampList();
	void LoadADCarryChampList();
	void LoadMagicanChampList();
	void LoadSupoterChampList();
	void LoadAssassinChampList();
	void ClassTypeCheck(int index);
};
