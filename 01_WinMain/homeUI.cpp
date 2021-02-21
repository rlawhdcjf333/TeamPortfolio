#include "pch.h"
#include "UI.h"
#include "TeamToggle.h"
#include "HomeToBattle.h"
#include "OperationToggle.h"
#include "LeagueToggle.h"
#include "GameToggle.h"
#include "SystemToggle.h"


void UI::homeUIInit() 
{

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new TeamToggle);
	ObjectManager::GetInstance()->FindObject("TeamToggle")->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new HomeToBattle);
	ObjectManager::GetInstance()->FindObject("HomeToBattle")->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new OperationToggle);
	ObjectManager::GetInstance()->FindObject("OperationToggle")->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new LeagueToggle);
	ObjectManager::GetInstance()->FindObject("LeagueToggle")->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new GameToggle);
	ObjectManager::GetInstance()->FindObject("GameToggle")->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new SystemToggle);
	ObjectManager::GetInstance()->FindObject("SystemToggle")->Init();
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

}