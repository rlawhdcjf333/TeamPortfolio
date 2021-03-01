#include "pch.h"
#include "Battle.h"
#include "Champ.h"
#include "Staff.h"

Battle::Battle() : UI("Battle")
{
	mIsActive = false;
}

void Battle::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BattleGround", Resources(L"battleback.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleGround");


}

void Battle::Release()
{
}

void Battle::Update()
{
	int myScore=0;

	myScore += mEnemyTeam[0]->GetDeathCount();
	myScore += mEnemyTeam[1]->GetDeathCount();
	myScore += mEnemyTeam[2]->GetDeathCount();

	int enemyScore=0;

	enemyScore += mMyTeam[0]->GetDeathCount();
	enemyScore += mMyTeam[1]->GetDeathCount();
	enemyScore += mMyTeam[2]->GetDeathCount();
	
	mMyScore = myScore;
	mEnemyScore = enemyScore;


}

void Battle::Render(HDC hdc)
{
	//1. 배경
	mImage->Render(hdc, 0, 0);
	//2. UI : 상단부분 + 좌우 정보 + 킬데스 -> BattleUI에서 표시
	//3. 챔프 : 이거는 챔프들이 알아서
}

void Battle::SetTeams(vector<Champ*> myTeam, vector<Champ*> enemyTeam)
{
	mMyTeam = myTeam;
	vector<GameObject*> myTeamList;
	myTeamList.assign(myTeam.begin(), myTeam.end());

	mEnemyTeam = enemyTeam;
	vector<GameObject*> enemyTeamList;
	enemyTeamList.assign(enemyTeam.begin(), enemyTeam.end());

	if(BData->GetPlayerTeam()==Team::Blue)
	{
		mMyTeam[0]->SetXY(400, 306);
		mMyTeam[0]->SetEnemyList(enemyTeamList);
		mMyTeam[0]->SetFriendList(myTeamList);
		mMyTeam[1]->SetXY(400, 441);
		mMyTeam[1]->SetEnemyList(enemyTeamList);
		mMyTeam[1]->SetFriendList(myTeamList);
		mMyTeam[2]->SetXY(400, 576);
		mMyTeam[2]->SetEnemyList(enemyTeamList);
		mMyTeam[2]->SetFriendList(myTeamList);

		mEnemyTeam[0]->SetXY(880, 306);
		mEnemyTeam[0]->SetEnemyList(myTeamList);
		mEnemyTeam[0]->SetFriendList(enemyTeamList);
		mEnemyTeam[1]->SetXY(880, 441);
		mEnemyTeam[1]->SetEnemyList(myTeamList);
		mEnemyTeam[1]->SetFriendList(enemyTeamList);
		mEnemyTeam[2]->SetXY(880, 576);
		mEnemyTeam[2]->SetEnemyList(myTeamList);
		mEnemyTeam[2]->SetFriendList(enemyTeamList);

	}
	else
	{
		mMyTeam[0]->SetXY(880, 306);
		mMyTeam[0]->SetEnemyList(enemyTeamList);
		mMyTeam[0]->SetFriendList(myTeamList);
		mMyTeam[1]->SetXY(880, 441);
		mMyTeam[1]->SetEnemyList(enemyTeamList);
		mMyTeam[1]->SetFriendList(myTeamList);
		mMyTeam[2]->SetXY(880, 576);
		mMyTeam[2]->SetEnemyList(enemyTeamList);
		mMyTeam[2]->SetFriendList(myTeamList);

		mEnemyTeam[0]->SetXY(400, 306);
		mEnemyTeam[0]->SetEnemyList(myTeamList);
		mEnemyTeam[0]->SetFriendList(enemyTeamList);
		mEnemyTeam[1]->SetXY(400, 441);
		mEnemyTeam[1]->SetEnemyList(myTeamList);
		mEnemyTeam[1]->SetFriendList(enemyTeamList);
		mEnemyTeam[2]->SetXY(400, 576);
		mEnemyTeam[2]->SetEnemyList(myTeamList);
		mEnemyTeam[2]->SetFriendList(enemyTeamList);
	}

	mWhole.clear();
	mWhole.shrink_to_fit();
	mWhole.emplace_back(mMyTeam[0]);
	mWhole.emplace_back(mMyTeam[1]);
	mWhole.emplace_back(mMyTeam[2]);
	mWhole.emplace_back(mEnemyTeam[0]);
	mWhole.emplace_back(mEnemyTeam[1]);
	mWhole.emplace_back(mEnemyTeam[2]);

	for (Champ* elem : mWhole)
	{
		elem->StaffOnChamp();
		elem->SetIsActive(true);
	}
}

void Battle::AllStop()
{
	for (Champ* elem : mWhole)
	{
		elem->SetIsActive(false);
	}
}
