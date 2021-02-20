#include "pch.h"
#include "Title.h"

#include "UI.h"
#include "BackGround.h"
#include "GameEvent.h"


void Title::Init()
{
	Background* background = new Background("Title", L"Title");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	UI* ui = new UI("titleUI", "titleUI");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);

	ObjectManager::GetInstance()->Init();

	GameEventManager::GetInstance()->RemoveAllEvent();
	IPrologueEvent* event1 = new IPrologueEvent();
	GameEventManager::GetInstance()->PushEvent(event1);

}

void Title::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Title::Update()
{
	ObjectManager::GetInstance()->Update();
}


void Title::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}
