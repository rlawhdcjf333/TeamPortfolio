#include "pch.h"
#include "UI.h"
#include <fstream>

UI::UI(const string& name, const string& fileName)
	:GameObject(name)
{
	mFileName = fileName;
}

void UI::Init()
{
	LoadFromFile(mFileName);

	if (mFileName == "homeUI") {

		homeUIInit();
	}

	

}

void UI::Release()
{
	
}

void UI::Update()
{

	if (mFileName == "titleUI") {

		auto func = []() {GameEventManager::GetInstance()->Update();};
		mSceneChangeButton(0, L"Home", true, func);
	
	}

	if (mFileName == "homeUI") {


		mToggleButton(0, "TeamToggle");


		mSceneChangeButton(5, L"Pick_Battle");

	}

	if (mFileName == "pick_battleUI") {

		mSceneChangeButton(0, L"Home");

	}



}

void UI::Render(HDC hdc)
{
	
	HBRUSH newb = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldb = (HBRUSH)SelectObject(hdc, newb);
	
	HPEN newp = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
	HPEN oldp = (HPEN)SelectObject(hdc, newp);

	for (RECT elem : mButtonList)
		RenderRect(hdc, elem);

	SelectObject(hdc, oldp);
	SelectObject(hdc, oldb);
	DeleteObject(newp);
	DeleteObject(newb);

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

void UI::mToggleButton(int index, string UIName)
{
	if (PtInRect(&mButtonList[index], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			GameObject* hptr = ObjectManager::GetInstance()->FindObject(UIName);
			hptr->SetIsActive(!hptr->GetIsActive());
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
			SceneManager::GetInstance()->LoadScene(nextSceneName);
		}
	}
}
