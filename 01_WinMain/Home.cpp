#include "pch.h"
#include "Home.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"
#include "Staff.h"


void Home::Init()
{

	Background* background = new Background("Home", L"Home");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	for(int i=0; i<4; i++)
	{
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff("Staff"+to_string(i+1), L"Staff"));
	}

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
