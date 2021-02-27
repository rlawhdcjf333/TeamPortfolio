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

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director1", L"TeamNuguri", L"TeamNuguri"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director2", L"TeamMansu", L"TeamMansu"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director3", L"TeamJoyRoom", L"TeamJoyRoom"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director4", L"TeamCowHead", L"TeamCowHead"));

	ChampManager::GetInstance()->Init();
	ScheduleManager::GetInstance()->Init();

	UI* ui = new UI("pickbattleUI", "pickbattleUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	ObjectManager::GetInstance()->Init();

	SoundPlayer::GetInstance()->AllPause();
	SoundPlayer::GetInstance()->Play(L"BanPick", 0.2f);

	GameEventManager::GetInstance()->PushEvent(new UIDelayEvent("StaffSelect",2.f));

	//--BData 호출
	
	Director* player = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	int thisWeek = player->GetWeek();
	if (thisWeek & 0)
	{
		BData->SetPlayerTeam(Team::Blue); //일단 존중
		BData->SetTeam(Team::Blue, player);
		BData->SetTeam(Team::Red, ScheduleManager::GetInstance()->GetEnemy(thisWeek));
	}
	else
	{
		BData->SetPlayerTeam(Team::Red);
		BData->SetTeam(Team::Red, player);
		BData->SetTeam(Team::Blue, ScheduleManager::GetInstance()->GetEnemy(thisWeek));
	}
	
}

void PickBattle::Release()
{
	ObjectManager::GetInstance()->Release();
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


