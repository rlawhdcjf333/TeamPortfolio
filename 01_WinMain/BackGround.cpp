#include "pch.h"
#include "Background.h"
#include "Image.h"
#include "Director.h"

Background::Background(const string& name, const wstring& fileName)
	: GameObject(name) 
{
	mFileName = fileName;
}

void Background::Init()
{
	IMAGEMANAGER->LoadFromFile(mFileName, Resources(mFileName+L".bmp"),1280,720, false);
	mImage = IMAGEMANAGER->FindImage(mFileName);

	if (mFileName == L"Title")
	{
		IMAGEMANAGER->LoadFromFile(L"TitleClearBuffer", Resources(L"TitleClearBuffer.bmp"), 1280, 720, false);
	}

}

void Background::Release()
{
}

void Background::Update()
{
}

void Background::Render(HDC hdc)
{
	mImage->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);

	if (mFileName == L"Audiences")
	{
		//까만색으로 변경
		SetTextColor(hdc, RGB(0, 0, 0));
		wstring leagueTitle = L"2021 경일 리그";
		CallFont(hdc, 24, [hdc, leagueTitle, this]() {TextOut(hdc, 576, 185, leagueTitle.c_str(), leagueTitle.size());});

		Director* player = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
		int week = player->GetWeek();
		Director* enemy =ScheduleManager::GetInstance()->GetEnemy(week);

		wstring round = to_wstring(week) + L" 라운드";
		CallFont(hdc, 24, [hdc, round]() {TextOut(hdc, 598, 212, round.c_str(), round.size());});

		//팀 마크 출력
		player->UIRender(hdc, 454, 185, 60, 60, false);
		player->UIRender(hdc, 330, 170, 40, 40, false);
		enemy->UIRender(hdc, 1280 - 454-60, 185, 60, 60, false);
		enemy->UIRender(hdc, 1280 - 330-40, 170, 40, 40, false);

		//팀 이름 출력
		wstring myTeam = player->GetTeamName();
		RECT myTeamRect = RectMakeCenter(484, 268, 180, 24);
		CallFont(hdc, 24, [hdc, myTeam, &myTeamRect] {DrawText(hdc, myTeam.c_str(), myTeam.size(), &myTeamRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);});
		
		wstring enemyTeam = enemy->GetTeamName();
		RECT enemyTeamRect = RectMakeCenter(1280-484, 268, 180, 24);
		CallFont(hdc, 24, [hdc, enemyTeam, &enemyTeamRect] {DrawText(hdc, enemyTeam.c_str(), enemyTeam.size(), &enemyTeamRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);});

		//팀 전적 출력
		wstring myRecord = to_wstring(player->GetRank()) + L"위  " + to_wstring(player->GetWin()) + L"승  " + to_wstring(player->GetLose()) + L"패  +" + to_wstring(player->GetLeagueScore());
		RECT rc1 = RectMakeCenter(484, 294, 180, 20);
		CallFont(hdc, 18, [hdc, myRecord, &rc1](){DrawText(hdc, myRecord.c_str(), myRecord.size(), &rc1, DT_VCENTER|DT_SINGLELINE|DT_CENTER);});
		
		wstring enemyRecord = to_wstring(enemy->GetRank()) + L"위  " + to_wstring(enemy->GetWin()) + L"승  " + to_wstring(enemy->GetLose()) + L"패  +" + to_wstring(enemy->GetLeagueScore());
		RECT rc2 = RectMakeCenter(1280-484, 294, 180, 20);
		CallFont(hdc, 18, [hdc, enemyRecord, &rc2]() {DrawText(hdc, enemyRecord.c_str(), enemyRecord.size(), &rc2, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});



		//흰색으로 변경
		SetTextColor(hdc, RGB(255, 255, 255));

		RECT playerTag = RectMake(68, 167, 250, 46);
		CallFont(hdc, 26, [hdc, myTeam, &playerTag] {DrawText(hdc, myTeam.c_str(), myTeam.size(), &playerTag, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);});

		RECT enemyTag = RectMake(1280 - 68 - 250, 167, 250, 46);
		CallFont(hdc, 26, [hdc, enemyTeam, &enemyTag] {DrawText(hdc, enemyTeam.c_str(), enemyTeam.size(), &enemyTag, DT_LEFT | DT_SINGLELINE | DT_VCENTER);});



	}


}
