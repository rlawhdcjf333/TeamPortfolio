#include "pch.h"
#include "UI.h"
#include "Child.h"

void UI::PickBattleUIInit()
{
	//1번째 : 스태프 선택
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new StaffSelect);	
	//2번째 : 밴픽
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new BanPick);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new ChampCheck);
}
void UI::PickBattleUIUpdate()
{
	//업데이트는 생성된 오브젝트의 mIsActive = true 이면 알아서 업데이트, 랜더 된다?
	function<void(void)> func;
	func = []() {

	};
}