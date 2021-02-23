#include "pch.h"
#include "UI.h"
#include "StaffSelect.h"

void UI::PickBattleUIInit()
{
	//mLevel = NULL;
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new StaffSelect);	
}
void UI::PickBattleUIUpdate()
{
	//업데이트는 생성된 오브젝트의 mIsActive = true 이면 알아서 업데이트, 랜더 된다?
	function<void(void)> func;
	func = []() {

	};
	/*
	switch (mLevel)	//레벨이 바뀌면 여기서 active세팅
	{
	case 1:

		if (ObjectManager::GetInstance()->FindObject("PeedBack")->GetIsActive())
		{
			ObjectManager::GetInstance()->FindObject("PeedBack")->SetIsActive(false);
		}
		if (!ObjectManager::GetInstance()->FindObject("StaffSelect")->GetIsActive())
		{
			ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		}
		break;
	default:
		break;
	}
	*/
}