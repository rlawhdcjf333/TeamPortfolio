#include "pch.h"
#include "Home.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"
#include "Director.h"
#include "Staff.h"


void Home::Init()
{

	Background* background = new Background("Home", L"Home");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director"+to_string(1), L"TeamNuguri", L"TeamNuguri"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director"+to_string(2), L"TeamMansu", L"TeamMansu"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director"+to_string(3), L"TeamJoyRoom", L"TeamJoyRoom"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director"+to_string(4), L"TeamCowHead", L"TeamCowHead"));

	UI* ui = new UI("homeUI", "homeUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

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
