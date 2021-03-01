#include "pch.h"
#include "PickBattle.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"
#include "Director.h"
#include "StaffSelect.h"

void PickBattle::Init()
{

	Background* background = new Background("Audiences", L"Audiences");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);
	
	ChampManager::GetInstance()->Init();
	BData->RoundReset();

	UI* ui = new UI("pickbattleUI", "pickbattleUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	ObjectManager::GetInstance()->Init();

	SoundPlayer::GetInstance()->AllPause();
	SoundPlayer::GetInstance()->Play(L"BanPick", 0.2f);

	GameEventManager::GetInstance()->PushEvent(new UIDelayEvent("StaffSelect",2.f));

	//--BData È£Ãâ
	
	Director* player = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	int thisWeek = player->GetWeek();
	Director* enemy = ScheduleManager::GetInstance()->GetEnemy(thisWeek);

	if (thisWeek & 0)
	{
		BData->SetPlayerTeam(Team::Blue); 
		BData->SetTeam(Team::Blue, player);
		BData->SetTeam(Team::Red, enemy);
	}
	else
	{
		BData->SetPlayerTeam(Team::Red);
		BData->SetTeam(Team::Red, player);
		BData->SetTeam(Team::Blue, enemy);
	}
	
}

void PickBattle::Release()
{
	ObjectManager::GetInstance()->Release();
	ChampManager::GetInstance()->SceneRelease();
}

void PickBattle::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

	ObjectManager::GetInstance()->Zorder();

}


void PickBattle::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

}


