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
	LoadFromFile("title");
}

void UI::Release()
{
}

void UI::Update()
{

	if (PtInRect(&mButtonList[0], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			SceneManager::GetInstance()->LoadScene(L"Home");
		}
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
