#include "pch.h"
#include "Home.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"


void Home::Init()
{
	Background* background = new Background("Home", L"Home");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);



	ObjectManager::GetInstance()->Init();
	EventCount = 0;
}

void Home::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Home::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

}


void Home::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}
