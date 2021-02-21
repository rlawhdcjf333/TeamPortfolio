#include "pch.h"
#include "UI.h"
#include "TeamToggle.h"
#include "HomeToBattle.h"


void UI::homeUIInit() 
{

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new TeamToggle);
	ObjectManager::GetInstance()->FindObject("TeamToggle")->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new HomeToBattle);
	ObjectManager::GetInstance()->FindObject("HomeToBattle")->Init();

	
}