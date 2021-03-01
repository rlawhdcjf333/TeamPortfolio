#pragma once
#include "UI.h"

class Champ;
class Battle : public UI
{
	Image* mImage;
	Image* mUI;
	int Count;	//юс╫ц

	vector<Champ*> mMyTeam;
	vector<Champ*> mEnemyTeam;
	vector<Champ*> mWhole;

	int mMyScore;
	int mEnemyScore;


public:
	Battle();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetTeams(vector<Champ*> myTeam, vector<Champ*> enemyTeam);
	void AllStop();
	int GetMyScore() { return mMyScore; }
	int GetEnemyScore() { return mEnemyScore; }
	void ResetScore() { mMyScore = 0; mEnemyScore = 0; }
};

