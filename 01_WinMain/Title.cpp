#include "pch.h"
#include "Title.h"

#include "BackGround.h"
#include "GameEvent.h"


void Title::Init()
{
	Background* background = new Background("Background", 0,0);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	
	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.0f));

	ObjectManager::GetInstance()->Init();
	EventCount = 0;
}

void Title::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Title::Update()
{
	ObjectManager::GetInstance()->Update();


	GameEventManager::GetInstance()->Update();
	
}


void Title::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}
