#include "pch.h"
#include "Home.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"
#include "Director.h"
#include "Staff.h"
#include "Schedule.h"


void Home::Init()
{

	Background* background = new Background("Home", L"Home");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	ChampManager::GetInstance()->Init();

	UI* ui = new UI("homeUI", "homeUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	ObjectManager::GetInstance()->Init();

	SoundPlayer::GetInstance()->AllPause();
	SoundPlayer::GetInstance()->Play(L"Warriors", 0.2f);

}

void Home::Release()
{
	ObjectManager::GetInstance()->Release();
	ChampManager::GetInstance()->SceneRelease();
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
