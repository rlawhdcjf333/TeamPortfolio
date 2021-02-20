#include "pch.h"
#include "Pick_Battle.h"

#include "BackGround.h"
#include "GameEvent.h"

void Pick_Battle::Init()
{

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
