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
	//������Ʈ�� ������ ������Ʈ�� mIsActive = true �̸� �˾Ƽ� ������Ʈ, ���� �ȴ�?
	function<void(void)> func;
	func = []() {

	};
	/*
	switch (mLevel)	//������ �ٲ�� ���⼭ active����
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