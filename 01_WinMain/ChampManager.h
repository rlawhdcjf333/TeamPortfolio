#pragma once

class GameObject;
class ChampManager
{
	Singleton(ChampManager);

	vector<GameObject*> mChampList;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SceneRelease();
	
	vector<GameObject*> GetChampList() const { return mChampList; }
};