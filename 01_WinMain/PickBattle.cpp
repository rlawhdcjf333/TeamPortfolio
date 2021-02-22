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
	EventCount = 0;
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

void PickBattle::Update1()
{
}

void PickBattle::Update2()
{
}

void PickBattle::Update3()
{
}

void PickBattle::Update4()
{
}

void PickBattle::Render1()
{
}

void PickBattle::Render2()
{
}

void PickBattle::Render3()
{
}

void PickBattle::Render4()
{
}
