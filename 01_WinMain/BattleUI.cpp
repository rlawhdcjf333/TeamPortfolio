#include "pch.h"
#include "BattleUI.h"
#include "Staff.h"
#include "Champ.h"
#include "Director.h"

BattleUI::BattleUI() : UI("BattleUI")
{
	mIsActive = false;
}

void BattleUI::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BattleUI", Resources(L"battleUI.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleUI");
	
	mTime = 60;
	mDeltaTime = 0.f;

	mPlayer = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	mEnemy = (Director*)ScheduleManager::GetInstance()->GetEnemy(mPlayer->GetWeek());

}

void BattleUI::Release()
{
}

void BattleUI::Update()
{
	if (!mIsActive)
	{
		return;
	}


	if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive())
	{
		if (mTime == 0 || Input::GetInstance()->GetKeyDown('G'))
		{
			//time == 0일때 킬수를 비교해서 킬을 많이한 팀이 그 경기 승리, 대회?는 2선승하면 승리 //연장전 어디가써
			ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("BattleResult")->SetIsActive(true);
			return;
		}
		mDeltaTime += Time::GetInstance()->DeltaTime();//델타타임 = 1프레임이 도는 시간, 1초를 구하려면? // 지금 상태는 1초에 1이 올라감
		if (mDeltaTime >= 1)
		{
			mDeltaTime = 0.f;
			mTime -= 1;
		}
	}
	else
	{
		mTime = 60;
	}
}

void BattleUI::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);

		if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive() == false)
		{
			wstring leagueName = L"2021 경일 리그 " + (to_wstring)(mPlayer->GetWeek()) + L"라운드";
			RECT nameBox = RectMake(550,58,180,22);
			CallFont(hdc, 15, [leagueName, hdc, &nameBox]() {DrawText(hdc, leagueName.c_str(), leagueName.size(), &nameBox, DT_VCENTER | DT_CENTER | DT_SINGLELINE);});
		}

		TeamRender(hdc);

		StaffInfoRender(hdc);

		if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive())	//배틀중일때
		{
			TextOut(hdc, 640, 60, to_wstring(mTime).c_str(), to_wstring(mTime).size());
		}
	}
}

void BattleUI::StaffInfoRender(HDC hdc)
{
	if (BData->GetPlayerTeam() == Team::Blue)
	{
		vector <Staff*> myTeam;
		myTeam.emplace_back(BData->GetSelectStaff(0));
		myTeam.emplace_back(BData->GetSelectStaff(1));
		myTeam.emplace_back(BData->GetSelectStaff(2));

		DrawStaff(hdc, 3, 80, myTeam, 0);
		DrawStaff(hdc, 3, 240, myTeam, 1);
		DrawStaff(hdc, 3, 400, myTeam, 2);

		vector <Staff*> enemyTeam;
		enemyTeam = BData->GetEnemyStaff();

		DrawStaff(hdc, 1125, 80, enemyTeam, 0);
		DrawStaff(hdc, 1125, 240, enemyTeam, 1);
		DrawStaff(hdc, 1125, 400, enemyTeam, 2);
	}
	else if (BData->GetPlayerTeam() == Team::Red)
	{
		vector <Staff*> myTeam;
		myTeam.emplace_back(BData->GetSelectStaff(0));
		myTeam.emplace_back(BData->GetSelectStaff(1));
		myTeam.emplace_back(BData->GetSelectStaff(2));

		DrawStaff(hdc, 1125, 80, myTeam, 0);
		DrawStaff(hdc, 1125, 240, myTeam, 1);
		DrawStaff(hdc, 1125, 400, myTeam, 2);

		vector <Staff*> enemyTeam;
		enemyTeam = BData->GetEnemyStaff();

		DrawStaff(hdc, 3, 80, enemyTeam, 0);
		DrawStaff(hdc, 3, 240, enemyTeam, 1);
		DrawStaff(hdc, 3, 400, enemyTeam, 2);

	}


}

void BattleUI::DrawStaff(HDC hdc, int x, int y, vector<Staff*> list, int i)
{
	//선수 i번 이름
	wstring enemyStaffName = StoW(list[i]->GetStaffName());
	CallFont(hdc, 30, [hdc, this, enemyStaffName, x, y]() {TextOut(hdc, x, y, enemyStaffName.c_str(), enemyStaffName.size()); });

	//선수 i번 컨디션
	list[i]->ConditionRender(hdc, 123 + x, 1 + y, 34, 29);

	//선수 i번 얼굴
	list[i]->UIRender(hdc, x + 1, y + 35, 52, 49);

	//선수 i번 특성
	wstring enemyStaffChar = list[i]->GetCharComment(1);
	CallFont(hdc, 15, [hdc, this, enemyStaffChar, x, y]() {TextOut(hdc, 89 + x, 42 + y, enemyStaffChar.c_str(), enemyStaffChar.size()); });

	//선수 i번 공격력
	wstring enemyStaffAtk = to_wstring(list[i]->GetAtk());
	CallFont(hdc, 17, [hdc, this, enemyStaffAtk, x, y]() {TextOut(hdc, 31 + x, 89 + y, enemyStaffAtk.c_str(), enemyStaffAtk.size()); });

	//선수 i번 방어력
	wstring enemyStaffDef = to_wstring(list[i]->GetDef());
	CallFont(hdc, 17, [hdc, this, enemyStaffDef, x, y]() {TextOut(hdc, 105 + x, 89 + y, enemyStaffDef.c_str(), enemyStaffDef.size()); });

	auto champList = list[i]->GetMostChamp();
	//선수 i번 모스트1
	CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake(x + 4, y + 115, 35, 35));});
	Champ* most1 = (Champ*)ObjectManager::GetInstance()->FindObject(champList.begin()->first);
	most1->UIRender(hdc, x + 4, y + 115, 35, 35);
	RECT ptBox1 = RectMake(x + 24, y + 115, 15, 15);
	CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox1, x, y]() {RenderRect(hdc, ptBox1);});
	wstring most1Pt = to_wstring(champList.begin()->second);
	CallFont(hdc, 15, [hdc, this, most1Pt, &ptBox1, x, y]() {DrawText(hdc, most1Pt.c_str(), most1Pt.size(), &ptBox1, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});

	//선수 i번 모스트2
	CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake(x + 44, y + 115, 35, 35));});
	Champ* most2 = (Champ*)ObjectManager::GetInstance()->FindObject(champList.rbegin()->first);
	most2->UIRender(hdc, x + 44, y + 115, 35, 35);
	RECT ptBox2 = RectMake(x + 64, y + 115, 15, 15);
	CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox2, x, y]() {RenderRect(hdc, ptBox2);});
	wstring most2Pt = to_wstring(champList.rbegin()->second);
	CallFont(hdc, 15, [hdc, this, most2Pt, &ptBox2, x, y]() {DrawText(hdc, most2Pt.c_str(), most2Pt.size(), &ptBox2, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});

}

void BattleUI::TeamRender(HDC hdc)
{
	if (BData->GetPlayerTeam() == Team::Blue)
	{
		mPlayer->TeamImageRender(hdc, 10, 4, 60, 60);

		wstring myTeam = mPlayer->GetTeamName();
		RECT myNameBox = RectMake(70, 0, 410, 70);
		CallFont(hdc, 30, [this, hdc, myTeam, &myNameBox]() {DrawText(hdc, myTeam.c_str(), myTeam.size(), &myNameBox, DT_CENTER|DT_VCENTER|DT_SINGLELINE);});
		
		wstring myScore = (to_wstring)(mPlayer->GetRound());
		RECT myScoreBox = RectMake(484, 4, 134, 50);
		CallFont(hdc, 35, [this, hdc, myScore, &myScoreBox]() {DrawText(hdc, myScore.c_str(), myScore.size(), &myScoreBox, DT_CENTER|DT_VCENTER|DT_SINGLELINE);});

		
		mEnemy->TeamImageRender(hdc, 1210, 4, 60, 60);

		wstring enemyTeam = mEnemy->GetTeamName();
		RECT enemyNameBox = RectMake(800, 0, 410, 70);
		CallFont(hdc, 30, [this, hdc, enemyTeam, &enemyNameBox]() {DrawText(hdc, enemyTeam.c_str(), enemyTeam.size(), &enemyNameBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});

		wstring enemyScore = (to_wstring)(mEnemy->GetRound());
		RECT enemyScoreBox = RectMake(1280 - 484 - 134, 4, 134, 50);
		CallFont(hdc, 35, [this, hdc, enemyScore, &enemyScoreBox]() {DrawText(hdc, enemyScore.c_str(), enemyScore.size(), &enemyScoreBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});

	}
	else if(BData->GetPlayerTeam() == Team::Red)
	{
		mEnemy->TeamImageRender(hdc, 10, 4, 60, 60);

		wstring enemyTeam = mEnemy->GetTeamName();
		RECT enemyNameBox = RectMake(70, 0, 410, 70);
		CallFont(hdc, 30, [this, hdc, enemyTeam, &enemyNameBox]() {DrawText(hdc, enemyTeam.c_str(), enemyTeam.size(), &enemyNameBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});

		wstring enemyScore = (to_wstring)(mEnemy->GetRound());
		RECT enemyScoreBox = RectMake(484, 4, 134, 50);
		CallFont(hdc, 35, [this, hdc, enemyScore, &enemyScoreBox]() {DrawText(hdc, enemyScore.c_str(), enemyScore.size(), &enemyScoreBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});


		mPlayer->TeamImageRender(hdc, 1210, 4, 60, 60);

		wstring myTeam = mPlayer->GetTeamName();
		RECT myNameBox = RectMake(800, 0, 410, 70);
		CallFont(hdc, 30, [this, hdc, myTeam, &myNameBox]() {DrawText(hdc, myTeam.c_str(), myTeam.size(), &myNameBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});

		wstring myScore = (to_wstring)(mPlayer->GetRound());
		RECT myScoreBox = RectMake(1280 - 484 - 134, 4, 134, 50);
		CallFont(hdc, 35, [this, hdc, myScore, &myScoreBox]() {DrawText(hdc, myScore.c_str(), myScore.size(), &myScoreBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});

	}


}
