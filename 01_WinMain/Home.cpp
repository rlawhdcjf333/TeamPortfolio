#include "pch.h"
#include "Home.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"
#include "Director.h"

void Home::Init()
{

	Background* background = new Background("Home", L"Home");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	UI* ui = new UI("homeUI", "homeUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("TeamNuguri", L"TeamNuguri"));
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("TeamMansu", L"TeamMansu"));
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("TeamCowHead", L"TeamCowHead"));
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("TeamJoyRoom", L"TeamJoyRoom"));

	ObjectManager::GetInstance()->Init();
}

void Home::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Home::Update()
{
	GameEventManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();

}


void Home::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}
