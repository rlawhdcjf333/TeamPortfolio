#include "pch.h"
#include "UI.h"
#include "Creators.h"


void UI::TitleUIInit ()
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Creators("Creators"));
	ObjectManager::GetInstance()->FindObject("Creators")->Init();
}

void UI::TitleUIUpdate ()
{
	function <void(void)> func = []()
	{
		ObjectManager::GetInstance()->FindObject("OnPatch")->SetIsActive(true);
	};
	mToggleButton(1, "OnPatch", func);

	func = []()
	{
		PostQuitMessage(0);
	};
	mToggleButton(2, "None", func);

	
	mToggleButton(3, "Creators");
	if (Input::GetInstance()->GetKeyUp('D'))
	{
		GameObject* hptr = ObjectManager::GetInstance()->FindObject("Creators");
		hptr->SetIsActive(!hptr->GetIsActive());
	}

	func = []()
	{
		GameEventManager::GetInstance()->Update();
	};
	mSceneChangeButton(0, L"Home", true, func);
}