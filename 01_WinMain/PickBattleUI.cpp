#include "pch.h"
#include "UI.h"
#include "StaffSelect.h"
#include "PickBattleUI.h"
void UI::PickBattleUIInit()
{
	mLevel = NULL;

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
	func("staffSelect", Level1Rect);
	//func("",Level2Rect);
	//func("",Level3Rect);
	//func("",Level4Rect);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new StaffSelect);
	ObjectManager::GetInstance()->FindObject("StaffSelect")->Init();
}
void UI::PickBattleUIUpdate()
{
	//업데이트는 생성된 오브젝트의 mIsActive = true 이면 알아서 업데이트, 랜더 된다?
	function<void(void)> func;
	func = []() {

	};
	switch (mLevel)
	{
	case 1:
		if (!ObjectManager::GetInstance()->FindObject("StaffSelect")->GetIsActive())
		{
			mButtonList = Level1Rect;
			ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(true);
		}
		//다음 레벨로 넘어갈때... (PickBattleUI cpp에서만 접근 가능한)mLevel을 (GameObject)Level안에서 변경해야하는데.... 어떻게하지
		//(GameObject)Level안에서 다음 단계로 넘어갈때 다음단계의 mIsActive = true 로 하고,
		//넘어간 다음에 이전단계 mIsActive = false ? 이러면 이상할거같은데
		break;
	default:
		break;
	}
}