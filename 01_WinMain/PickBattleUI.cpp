#include "pch.h"
#include "UI.h"
#include "StaffSelect.h"
#include "PickBattleUI.h"
void UI::PickBattleUIInit()
{
	mLevel = NULL;
	/*�ϴ� �ּ� �Ʒ� return�־ ���ص��ɰŰ���
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
	func("staffSelect", Level1Rect); //?? ���� �̰Ž� ...����ö LoadFromFile() �̰� �Ⱦ�?
	//func("banPick",Level2Rect);
	//func("battle",Level3Rect);
	//func("peedBack",Level4Rect);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new StaffSelect);
	ObjectManager::GetInstance()->FindObject("StaffSelect")->Init();
}
void UI::PickBattleUIUpdate()
{
	//������Ʈ�� ������ ������Ʈ�� mIsActive = true �̸� �˾Ƽ� ������Ʈ, ���� �ȴ�?
	function<void(void)> func;
	func = []() {

	};
	switch (mLevel)	//������ �ٲ�� ���⼭ active����
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