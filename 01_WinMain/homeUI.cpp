#include "pch.h"
#include "UI.h"
#include "TeamToggle.h"
#include "HomeToBattle.h"
#include "OperationToggle.h"
#include "LeagueToggle.h"
#include "GameToggle.h"
#include "SystemToggle.h"
#include "Director.h"


void UI::homeUIInit() 
{

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new TeamToggle);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new HomeToBattle);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new OperationToggle);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new LeagueToggle);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new GameToggle);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new SystemToggle);
}

void UI::homeUIUpdate()
{
	function <void(void)> ffunc = []() {
		function <void(string)> func = [](string str)
		{
			ObjectManager::GetInstance()->FindObject(str)->SetIsActive(false);
		};

		func("OperationToggle");
		func("LeagueToggle");
		func("GameToggle");
		func("SystemToggle");
	};
	mToggleButton(0, "TeamToggle", ffunc);

	ffunc = []() {
		function <void(string)> func = [](string str)
		{
			ObjectManager::GetInstance()->FindObject(str)->SetIsActive(false);
		};

		func("TeamToggle");
		func("LeagueToggle");
		func("GameToggle");
		func("SystemToggle");
	};
	mToggleButton(1, "OperationToggle", ffunc);

	
	ffunc = []() {
		function <void(string)> func = [](string str)
		{
			ObjectManager::GetInstance()->FindObject(str)->SetIsActive(false);
		};
		func("OperationToggle");
		func("TeamToggle");
		func("GameToggle");
		func("SystemToggle");
	};
	mToggleButton(2, "LeagueToggle", ffunc);

	ffunc = []() {
		function <void(string)> func = [](string str)
		{
			ObjectManager::GetInstance()->FindObject(str)->SetIsActive(false);
		};
		func("OperationToggle");
		func("LeagueToggle");
		func("TeamToggle");
		func("SystemToggle");
	};
	mToggleButton(3, "GameToggle", ffunc);

	ffunc = []() {
		function <void(string)> func = [](string str)
		{
			ObjectManager::GetInstance()->FindObject(str)->SetIsActive(false);
		};
		func("OperationToggle");
		func("LeagueToggle");
		func("TeamToggle");
		func("GameToggle");
	};
	mToggleButton(4, "SystemToggle", ffunc);


	mToggleButton(5, "HomeToBattle");

	if (Input::GetInstance()->GetKeyUp('Y'))
	{
		GameObject* tmp = ObjectManager::GetInstance()->FindObject("HomeToBattle");
		tmp->SetIsActive(!tmp->GetIsActive());
	}

}

void UI::homeUIRender(HDC hdc) 
{

	Director* tmp = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	tmp->UIRender(hdc, 20, 5, 55, 55);

}