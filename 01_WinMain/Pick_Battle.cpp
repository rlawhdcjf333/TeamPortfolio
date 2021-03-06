#include "pch.h"
#include "Pick_Battle.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"

void Pick_Battle::Init()
{
	Background* background = new Background("Audiences", L"Audiences");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	UI* ui = new UI("pick_battleUI", "pick_battleUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, ui);

	ObjectManager::GetInstance()->Init();
	EventCount = 0;



}

void Pick_Battle::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Pick_Battle::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
}

void Pick_Battle::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

}

void Pick_Battle::Update1()
{
}

void Pick_Battle::Update2()
{
}

void Pick_Battle::Update3()
{
}

void Pick_Battle::Update4()
{
}

void Pick_Battle::Render1()
{
}

void Pick_Battle::Render2()
{
}

void Pick_Battle::Render3()
{
}

void Pick_Battle::Render4()
{
}
