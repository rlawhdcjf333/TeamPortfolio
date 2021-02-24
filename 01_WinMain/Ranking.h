#pragma once
#include "UI.h"

class Director;
class Ranking : public UI {
	Image* mImage;

	Director* mDirector;
	vector<Director*> mDirectorList;
public :
	Ranking();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void LoadDirectorList();
};