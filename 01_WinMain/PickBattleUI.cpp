#include "pch.h"
#include "UI.h"
#include "Child.h"

void UI::PickBattleUIInit()
{
	//1��° : ������ ����
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new StaffSelect);	
	//2��° : ����
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new BanPick);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new ChampCheck);
}
void UI::PickBattleUIUpdate()
{
	//������Ʈ�� ������ ������Ʈ�� mIsActive = true �̸� �˾Ƽ� ������Ʈ, ���� �ȴ�?
	function<void(void)> func;
	func = []() {

	};
}