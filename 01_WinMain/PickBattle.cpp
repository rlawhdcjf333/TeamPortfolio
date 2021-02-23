#include "pch.h"
#include "PickBattle.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"

void PickBattle::Init()
{

	Background* background = new Background("Audiences", L"Audiences");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	UI* ui = new UI("pickbattleUI", "pickbattleUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, ui);

	ObjectManager::GetInstance()->Init();
	GameEventManager::GetInstance()->PushEvent(new UIDelayEvent("StaffSelect",2.f));

	SoundPlayer::GetInstance()->AllPause();
	SoundPlayer::GetInstance()->Play(L"BanPick", 0.2f);
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
