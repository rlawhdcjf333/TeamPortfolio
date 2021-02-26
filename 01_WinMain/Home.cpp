#include "pch.h"
#include "Home.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"
#include "Director.h"
#include "Staff.h"
#include "ChampManager.h"

void Home::Init()
{

	Background* background = new Background("Home", L"Home");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	ChampManager::GetInstance()->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director1", L"TeamNuguri", L"TeamNuguri"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director2", L"TeamMansu", L"TeamMansu"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director3", L"TeamJoyRoom", L"TeamJoyRoom"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Director, new Director("Director4", L"TeamCowHead", L"TeamCowHead"));

	ScheduleManager::GetInstance()->Init();

	UI* ui = new UI("homeUI", "homeUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	ObjectManager::GetInstance()->Init();

	SoundPlayer::GetInstance()->AllPause();
	SoundPlayer::GetInstance()->Play(L"Warriors", 0.2f);

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
