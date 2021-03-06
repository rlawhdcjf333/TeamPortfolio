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
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new BanPickGuide);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new ChampSelect);
	//3번째 : 배틀
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Battle);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new BattleResult);
	//4번째 : 피드백
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Feedback);

	//제일 위에 표시할 ui
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new BattleUI);
}
void UI::PickBattleUIUpdate()
{
	//업데이트는 생성된 오브젝트의 mIsActive = true 이면 알아서 업데이트, 랜더 된다? //그렇소
	function<void(void)> func;
	func = []() {

	};
}