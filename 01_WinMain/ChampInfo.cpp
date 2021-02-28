#include "pch.h"
#include "ChampInfo.h"
#include "ChampManager.h"
#include "Champ.h"
#include "ChampInformation.h"

ChampInfo::ChampInfo()
	:UI("ChampInfo")
{
	mIsActive = false;
}

void ChampInfo::Init()
{
	LoadFromFile("ChampInfo");

	IMAGEMANAGER->LoadFromFile(L"ChampInfo", Resources(L"ChampInfo.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"ChampInfo");

	LoadAllChampList();

	for (int i = 0; i < mChampList.size(); i++) {
		mCurrentRectList.push_back(RectMake(49 + (i * 125), 155, 110, 175));
	}

	ofstream fout("../rectList/ChampInfoRectList.txt");

	for (RECT elem : mCurrentRectList) {

		fout << to_string(elem.left) << endl
			<< to_string(elem.top) << endl
			<< to_string(elem.right) << endl
			<< to_string(elem.bottom) << endl;

	}

	fout.close();

	mChampInformation = new ChampInformation();
	mChampInformation->Init();
}

void ChampInfo::Release()
{
	mChampInformation->Release();
	SafeDelete(mChampInformation);
}

void ChampInfo::Update()
{

	if (mIsActive)
	{
		ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("HomeToBattle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);

		mChampInformation->Update();

		auto func1 = [this]() {	LoadAllChampList();	};
		auto func2 = [this]() {	LoadWarriorChampList(); };
		auto func3 = [this]() {	LoadADCarryChampList();	};
		auto func4 = [this]() {	LoadMagicianChampList(); };
		auto func5 = [this]() {	LoadSupporterChampList(); };
		auto func6 = [this]() {	LoadAssassinChampList(); };
		auto func7 = [this]() {	mIsActive = false; };

		if (!mChampInformation->GetIsActive()) {
			mToggleButton(0, "None", func1);
			mToggleButton(1, "None", func2);
			mToggleButton(2, "None", func3);
			mToggleButton(3, "None", func4);
			mToggleButton(4, "None", func5);
			mToggleButton(5, "None", func6);
			mToggleButton(6, "None", func7);

			
		}

		mCurrentRectList.clear();
		mCurrentRectList.shrink_to_fit();

		for (int i = 0; i < mChampList.size(); i++) {
			mCurrentRectList.push_back(RectMake(49 + (i * 125), 155, 110, 175));
		}

		ofstream fout("../rectList/ChampInfoRectList.txt");

		for (RECT elem : mCurrentRectList) {

			fout << to_string(elem.left) << endl
				<< to_string(elem.top) << endl
				<< to_string(elem.right) << endl
				<< to_string(elem.bottom) << endl;

		}

		fout.close();

		LoadFromFile("ChampInfo", "ChampInfoRectList");

	
		for (int i = 0; i < mChampList.size(); i++) {
			if (PtInRect(&mButtonList[i + 7], _mousePosition)) {
				if (Input::GetInstance()->GetKeyDown(VK_LBUTTON) && (!mChampInformation->GetIsActive())) {
					vector<Champ*> champList;
					for (int x = 0; x < mChampList.size(); x++) {
						Champ* temp = (Champ*)mChampList[x];
						champList.push_back(temp);
					}

					mChampInformation->SetChampList(champList);
					mChampInformation->SetCurrentChamp(champList[i]);
					mChampInformation->SetIsActive(true);

					break;
				}
			}
		}
		
	}

}

void ChampInfo::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
		MouseOver(hdc);

		vector<RECT> rectList;
		for (int i = 0; i < mChampList.size(); i++) {
			rectList.push_back(RectMake(49 + (i * 125), 155, 110, 25));
			rectList.push_back(RectMake(49 + (i * 125), 180, 110, 115));
			rectList.push_back(RectMake(49 + (i * 125), 295, 110, 35));
		}

		for (int i = 0; i < mChampList.size(); i++) {

			HBRUSH newB = CreateSolidBrush(RGB(53, 58, 61));
			HBRUSH oldB = (HBRUSH)SelectObject(hdc, newB);
			RenderRect(hdc, rectList[1 + (i * 3)]);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			newB = CreateSolidBrush(RGB(17, 19, 23));
			oldB = (HBRUSH)SelectObject(hdc, newB);
			RenderRect(hdc, rectList[0 + (i * 3)]);
			RenderRect(hdc, rectList[2 + (i * 3)]);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			Champ* champ = (Champ*)mChampList[i];
			champ->ChampImageRender(hdc, rectList[1 + (i * 3)]);

			ClassTypeCheck(i);

			wstring temp = champ->GetChampName();
			wstring champClass = L"  " + mClassTypeName;
			wstring champName;
			champName.assign(temp.begin(), temp.end());

			HFONT newF = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			HFONT oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, champName.c_str(), champName.length(), &rectList[2 + (i * 3)], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);

			newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, champClass.c_str(), champClass.length(), &rectList[0 + (i * 3)], DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);
		}

	}

	mChampInformation->Render(hdc);
}

void ChampInfo::LoadAllChampList()
{
	mChampList = ChampManager::GetInstance()->GetChampList();
}

void ChampInfo::LoadWarriorChampList()
{
	vector<GameObject*> temp = ChampManager::GetInstance()->GetChampList();
	vector<Champ*> champTemp;
	for (int i = 0; i < temp.size(); i++) {
		Champ* champ = (Champ*)temp[i];
		if (champ->GetClassType() == ClassType::Warrior) {
			champTemp.push_back(champ);
		}
	}

	mChampList.assign(champTemp.begin(), champTemp.end());
}

void ChampInfo::LoadADCarryChampList()
{
	vector<GameObject*> temp = ChampManager::GetInstance()->GetChampList();
	vector<Champ*> champTemp;
	for (int i = 0; i < temp.size(); i++) {
		Champ* champ = (Champ*)temp[i];
		if (champ->GetClassType() == ClassType::ADCarry) {
			champTemp.push_back(champ);
		}
	}

	mChampList.assign(champTemp.begin(), champTemp.end());
}

void ChampInfo::LoadMagicianChampList()
{
	vector<GameObject*> temp = ChampManager::GetInstance()->GetChampList();
	vector<Champ*> champTemp;
	for (int i = 0; i < temp.size(); i++) {
		Champ* champ = (Champ*)temp[i];
		if (champ->GetClassType() == ClassType::Magician) {
			champTemp.push_back(champ);
		}
	}

	mChampList.assign(champTemp.begin(), champTemp.end());
}

void ChampInfo::LoadSupporterChampList()
{
	vector<GameObject*> temp = ChampManager::GetInstance()->GetChampList();
	vector<Champ*> champTemp;
	for (int i = 0; i < temp.size(); i++) {
		Champ* champ = (Champ*)temp[i];
		if (champ->GetClassType() == ClassType::Supporter) {
			champTemp.push_back(champ);
		}
	}

	mChampList.assign(champTemp.begin(), champTemp.end());
}

void ChampInfo::LoadAssassinChampList()
{
	vector<GameObject*> temp = ChampManager::GetInstance()->GetChampList();
	vector<Champ*> champTemp;
	for (int i = 0; i < temp.size(); i++) {
		Champ* champ = (Champ*)temp[i];
		if (champ->GetClassType() == ClassType::Assassin) {
			champTemp.push_back(champ);
		}
	}

	mChampList.assign(champTemp.begin(), champTemp.end());
}

void ChampInfo::ClassTypeCheck(int index)
{
	Champ* champ = (Champ*)mChampList[index];
	switch (champ->GetClassType())
	{
	case ClassType::Warrior:
		mClassTypeName = L"전사";
		break;
	case ClassType::ADCarry:
		mClassTypeName = L"원거리";
		break;
	case ClassType::Magician:
		mClassTypeName = L"마법사";
		break;
	case ClassType::Supporter:
		mClassTypeName = L"전투 보조";
		break;
	case ClassType::Assassin:
		mClassTypeName = L"암살자";
		break;
	}
	
}

void ChampInfo::AssignFromFile(string fileName)
{
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

		vector <RECT> tmpVector;
		for (int i = 0; i < v.size(); i += 4) {
			RECT rc = { v[i], v[i + 1], v[i + 2], v[i + 3] };
			tmpVector.push_back(rc);
		}

		mButtonList.assign(tmpVector.begin(), tmpVector.end());	
	}

	fin.close();

}