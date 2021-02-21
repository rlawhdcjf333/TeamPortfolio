#include "pch.h"
#include "Home.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"


void Home::Init()
{
	


	ObjectManager::GetInstance()->FindObject(ObjectLayer::Director, "dir");
	if (Storage::GetInstance->FindObject()) {
		ObjectManager::GetInstance()->FindObject(ObjectLayer::Director, "dir") = Storage::GetInstance->FindObject();

	}

	Background* background = new Background("Home", L"Home");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

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
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

}


void Home::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}
