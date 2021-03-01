#include "pch.h"
#include "BattleResult.h"
#include "Director.h"
#include "Battle.h"

BattleResult::BattleResult() : UI("BattleResult")
{
	mIsActive = false;
}

void BattleResult::Init()
{
	LoadFromFile("BattleResult");
	IMAGEMANAGER->LoadFromFile(L"BattleResult", Resources(L"BattleResult.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleResult");
}

void BattleResult::Update()
{
	if (!mIsActive)
		return;
	//배틀 씬 종료 트리거
	function<void(void)> func;
	if (BData->IsEnd())
	{
		
		func = []()
		{
			Director* player = BData->GetMyDirector();
			Director* enemy = BData->GetEnemyDirector();
			int today = player->GetWeek();
			if (player->GetRound() == 2) { player->PlusWin(); enemy->PlusLose(); player->RandGold();}
			else { player->PlusLose(); enemy->PlusWin(); }
			int x = Random::GetInstance()->RandomInt(0, 1);
			if (x == 0)
			{
				ScheduleManager::GetInstance()->GetOutFight1(today)->PlusWin();
				ScheduleManager::GetInstance()->GetOutFight2(today)->PlusLose();
			}
			else
			{
				ScheduleManager::GetInstance()->GetOutFight2(today)->PlusWin();
				ScheduleManager::GetInstance()->GetOutFight1(today)->PlusLose();
			}
			ScheduleManager::GetInstance()->GetPlayer(today)->CalLeagueScore();
			ScheduleManager::GetInstance()->GetEnemy(today)->CalLeagueScore();
			ScheduleManager::GetInstance()->GetOutFight1(today)->CalLeagueScore();
			ScheduleManager::GetInstance()->GetOutFight2(today)->CalLeagueScore();
			vector<Director*> newlist;
			newlist.push_back(ScheduleManager::GetInstance()->GetPlayer(today));
			newlist.push_back(ScheduleManager::GetInstance()->GetEnemy(today));
			newlist.push_back(ScheduleManager::GetInstance()->GetOutFight1(today));
			newlist.push_back(ScheduleManager::GetInstance()->GetOutFight2(today));
			auto funcc = [](Director* a, Director* b){
				if (a->GetLeagueScore() == b->GetLeagueScore())
				{
					return a->GetName() < b->GetName();
				}
				return a->GetLeagueScore() > b->GetLeagueScore();
			};
			sort(newlist.begin(), newlist.end(), funcc);
			for (int i = 0; i < 4; i++)
			{
				newlist[i]->SetRank(i+1);
			}
			player->PlusWeek();
			SceneManager::GetInstance()->LoadScene(L"Home"); 
		};
	}
	else //배틀 씬 반복 트리거
	{
		func = []()
		{
			Battle* battle = (Battle*)ObjectManager::GetInstance()->FindObject("Battle");
			battle->ResetScore();
			ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("Feedback")->SetIsActive(true);
		};
	}

	if (Input::GetInstance()->GetKeyDown('F'))
	{
	
		ObjectManager::GetInstance()->FindObject("BattleResult")->SetIsActive(false);
		func();
	}
	mToggleButton(0, "BattleResult", func);
}

void BattleResult::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);

		Battle* battle = (Battle*)ObjectManager::GetInstance()->FindObject("Battle");
		int myScore = battle->GetMyScore();
		int enemyScore = battle->GetEnemyScore();
		if (myScore > enemyScore)
		{
			wstring a = L"승리";
			CallFont(hdc, 35, [hdc,a]() {TextOut(hdc, 609,276,a.c_str(), a.length());});
		}
		else
		{
			wstring a = L"패배";
			CallFont(hdc, 35, [hdc, a]() {TextOut(hdc, 609, 276, a.c_str(), a.length());});
		}

		BData->GetMyDirector()->TeamImageRender(hdc, 485, 381, 60, 60);
		wstring myRound = to_wstring(BData->GetWinCount(BData->GetPlayerTeam()));
		RECT myRc = RectMake(590, 390, 40, 40);
		CallFont(hdc, 40, [&myRc, myRound, hdc]() {DrawText(hdc, myRound.c_str(), myRound.size(), &myRc, DT_VCENTER|DT_SINGLELINE|DT_CENTER);});
		
		BData->GetEnemyDirector()->TeamImageRender(hdc, 1280 - 485 - 60, 381, 60, 60);
		wstring enemyRound = to_wstring(BData->GetWinCount(BData->GetEnemyTeam()));
		RECT enemyRc = RectMake(650, 390, 40, 40);
		CallFont(hdc, 40, [&enemyRc, enemyRound, hdc]() {DrawText(hdc, enemyRound.c_str(), enemyRound.size(), &enemyRc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});

		 
	}
}
