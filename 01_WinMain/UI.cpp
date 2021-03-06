#include "pch.h"
#include "UI.h"
#include "OnPatch.h"

UI::UI(const string& name)
	:GameObject(name) 
{
	mMouseOverOn = true;
	mIsActive = false;
}

UI::UI(const string& name, const string& fileName)
	: GameObject(name), mFileName(fileName) {}

void UI::Init()
{
	LoadFromFile(mFileName);

	if (mFileName == "titleUI")
	{
		TitleUIInit();
	}

	if (mFileName == "homeUI") 
	{
		homeUIInit();
	}

	if (mFileName == "pickbattleUI")
	{
		PickBattleUIInit();
	}

	mMouseOverOn = true;
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, new OnPatch("OnPatch"));
}

void UI::Release()
{
	
}

void UI::Update()
{
	if (mFileName == "titleUI") 
	{
		TitleUIUpdate();
	}

	if (mFileName == "homeUI") 
	{
		homeUIUpdate();
	}

	if (mFileName == "pickbattleUI")
	{
		PickBattleUIUpdate();
	}

}

void UI::Render(HDC hdc)
{
	
	MouseOver(hdc);

	if (mFileName == "homeUI")
	{
		homeUIRender(hdc);
	}

}

void UI::LoadFromFile(const string& fileName)
{
	ifstream fin("../rectList/"+fileName+".txt");
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
			mButtonList.push_back(rc);
		}

	}

	fin.close();
}

void UI::LoadFromFile(const string& fileName1, const string& fileName2)
{
	mButtonList.clear();
	mButtonList.shrink_to_fit();

	ifstream fin1("../rectList/" + fileName1 + ".txt");
	if (fin1.is_open()) {

		vector <int> v;
		string tmp;
		int tmpint;

		while (fin1) {

			getline(fin1, tmp);
			if (tmp.size()) {
				tmpint = stoi(tmp);
				v.push_back(tmpint);
			}

		}


		for (int i = 0; i < v.size(); i += 4) {
			RECT rc = { v[i], v[i + 1], v[i + 2], v[i + 3] };
			mButtonList.push_back(rc);
		}

	}

	fin1.close();

	ifstream fin2("../rectList/" + fileName2 + ".txt");
	if (fin2.is_open()) {

		vector <int> v;
		string tmp;
		int tmpint;

		while (fin2) {

			getline(fin2, tmp);
			if (tmp.size()) {
				tmpint = stoi(tmp);
				v.push_back(tmpint);
			}

		}


		for (int i = 0; i < v.size(); i += 4) {
			RECT rc = { v[i], v[i + 1], v[i + 2], v[i + 3] };
			mButtonList.push_back(rc);
		}

	}

	fin2.close();
}

void UI::MouseOver(HDC hdc)
{
	if (mMouseOverOn)
	{
		for (int index = 0; index < mButtonList.size(); index++)
		{

			HBRUSH newB = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldB = (HBRUSH)SelectObject(hdc, newB);
			HPEN newP = CreatePen(PS_SOLID, 5, RGB(95, 223, 0));
			HPEN oldP = (HPEN)SelectObject(hdc, newP);
			if (PtInRect(&mButtonList[index], _mousePosition)) {
	
				RenderRect(hdc, mButtonList[index]);
			}
			SelectObject(hdc, oldB);
			DeleteObject(newB);
			SelectObject(hdc, oldP);
			DeleteObject(newP);
		}
	}

}

void UI::mToggleButton(int index, string UIName, function <void(void)> func)
{
	if (PtInRect(&mButtonList[index], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			if (UIName == "OnPatch")
			{
				OnPatch* tmp = (OnPatch*)ObjectManager::GetInstance()->FindObject(UIName);
				tmp->SetIsActive(true);
				tmp->ResetCurrentTime();
			}
			else if (UIName != "None")
			{
				GameObject* hptr = ObjectManager::GetInstance()->FindObject(UIName);
				hptr->SetIsActive(!hptr->GetIsActive());
			}
			func();
			
		}
	}
}

void UI::mSceneChangeButton(int index, wstring nextSceneName, bool sceneEvent, function <void(void)> func)
{

	if (sceneEvent == false) {
		if (PtInRect(&mButtonList[index], _mousePosition)) {

			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

				SceneManager::GetInstance()->LoadScene(nextSceneName);
			}
		}
	}
	else {
		if (PtInRect(&mButtonList[index], _mousePosition)) {

			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

				mTrigger = true;
			}
		}
		if (mTrigger)
		{
			func();
		}
		if (!GameEventManager::GetInstance()->IsPlaying()) {
			mTrigger = false;
			SceneManager::GetInstance()->LoadScene(nextSceneName);
		}
	}
}
