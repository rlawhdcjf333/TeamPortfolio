#include "pch.h"
#include "UI.h"
#include "StaffSelect.h"
#include "PickBattleUI.h"
void UI::PickBattleUIInit()
{
	mLevel = NULL;
	/*일단 주석 아래 return있어서 안해도될거같고
	Level1Rect.clear();
	Level1Rect.shrink_to_fit();
	Level2Rect.clear();
	Level2Rect.shrink_to_fit();
	Level3Rect.clear();
	Level3Rect.shrink_to_fit();
	Level4Rect.clear();
	Level4Rect.shrink_to_fit();
	*/

	PickBattleUI mUI;
	//mUI.mEnemyStaff = ObjectManager::GetObjectList(ObjectLayer::Staff)
	function<void(string, vector<RECT>)> func = [](string fileName, vector<RECT>rcList)
	{
		if (rcList.size() > 0)
			return;
		ifstream fin("../rectList/" + fileName + ".txt");
		if (fin.is_open()) {

			vector <int> v;
			string tmp;
			int tmpint;

			while (fin) {

				getline(fin, tmp);
				if (tmp.size()) {
					tmpint = stoi(tmp);
					v.push_back(tmpint);
				}

			}


			for (int i = 0; i < v.size(); i += 4) {
				RECT rc = { v[i], v[i + 1], v[i + 2], v[i + 3] };
				rcList.push_back(rc);
			}

		}

		fin.close();
	};
	func("staffSelect", Level1Rect); //?? 무여 이거시 ...김종철 LoadFromFile() 이거 안씀?
	//func("banPick",Level2Rect);
	//func("battle",Level3Rect);
	//func("peedBack",Level4Rect);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new StaffSelect);
	ObjectManager::GetInstance()->FindObject("StaffSelect")->Init();
}
void UI::PickBattleUIUpdate()
{
	//업데이트는 생성된 오브젝트의 mIsActive = true 이면 알아서 업데이트, 랜더 된다?
	function<void(void)> func;
	func = []() {

	};
	switch (mLevel)	//레벨이 바뀌면 여기서 active세팅
	{
	case 1:

		if (ObjectManager::GetInstance()->FindObject("PeedBack")->GetIsActive())
		{
			ObjectManager::GetInstance()->FindObject("PeedBack")->SetIsActive(false);
		}
		if (!ObjectManager::GetInstance()->FindObject("StaffSelect")->GetIsActive())
		{
			mButtonList = Level1Rect;
			ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		}
		break;
	default:
		break;
	}
}