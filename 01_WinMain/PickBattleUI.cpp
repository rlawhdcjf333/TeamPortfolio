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
	//3번째 : 배틀
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Battle);
	//4번째 진행 전에 경기결과 추가해야함...
	//4번째 : 피드백
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new Peedback);
}
void UI::PickBattleUIUpdate()
{
	//업데이트는 생성된 오브젝트의 mIsActive = true 이면 알아서 업데이트, 랜더 된다?
	function<void(void)> func;
	func = []() {

	};
}