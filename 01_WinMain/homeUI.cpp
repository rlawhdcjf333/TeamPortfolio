#include "pch.h"
#include "UI.h"
#include "TeamToggle.h"

void UI::homeUIInit() 
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new TeamToggle);
	ObjectManager::GetInstance()->FindObject("TeamToggle")->Init();





}