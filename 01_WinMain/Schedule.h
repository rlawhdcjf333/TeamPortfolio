#pragma once
#include "UI.h"

class Director;
class Schedule : public UI
{
	Image* mImage;
	Director* mDirector;

	vector<GameObject*> mDirectorList;
	map<int, vector<Director*>> mScheduleList;
public :
	Schedule();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void LoadDirectorList();

	void SetScheduleUI(map<int, vector<Director*>> list);
	
};