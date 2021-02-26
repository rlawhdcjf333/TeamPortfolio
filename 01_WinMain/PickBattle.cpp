#include "pch.h"
#include "PickBattle.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"
#include "Director.h"

void PickBattle::Init()
{

	Background* background = new Background("Audiences", L"Audiences");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director1", L"TeamNuguri", L"TeamNuguri"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director2", L"TeamMansu", L"TeamMansu"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director3", L"TeamJoyRoom", L"TeamJoyRoom"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director4", L"TeamCowHead", L"TeamCowHead"));

	UI* ui = new UI("pickbattleUI", "pickbattleUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, ui);

	ObjectManager::GetInstance()->Init();
	GameEventManager::GetInstance()->PushEvent(new UIDelayEvent("StaffSelect",2.f));

	SoundPlayer::GetInstance()->AllPause();
	SoundPlayer::GetInstance()->Play(L"BanPick", 0.2f);

	//--BData »£√‚
	
	map<int,vector<Director*>> temp = ScheduleManager::GetInstance()->GetSchedule();//map
	GameObject* tp = ObjectManager::GetInstance()->FindObject("Director1");
	Director* nugul = (Director*)tp;
	int key = nugul->GetRound();
	vector<Director*> tempList = ScheduleManager::GetInstance()->GetDayDirector(1);
	BData->SetPlayerTeam(Team::Blue);
	BData->SetTeam(Team::Blue, nugul);
	BData->SetTeam(Team::Red, tempList[1]);
	
	//--
}

void PickBattle::Release()
{
	ObjectManager::GetInstance()->Release();
}

void PickBattle::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();


}


void PickBattle::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

}


