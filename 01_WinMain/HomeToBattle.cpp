#include "pch.h"
#include "HomeToBattle.h"


HomeToBattle::HomeToBattle()
	:GameObject("HomeToBattle")
{
	mIsActive = false;
}

void HomeToBattle::Init()
{
	LoadFromFile("HomeToBattle");

	IMAGEMANAGER->LoadFromFile(L"HomeToBattle", Resources(L"HomeToBattle.bmp"), 353, 229, true);
	mImage = IMAGEMANAGER->FindImage(L"HomeToBattle");
}

void HomeToBattle::Release()
{
}

void HomeToBattle::Update()
{
	if (mIsActive)
	{
		if (PtInRect(&mButtonList[0], _mousePosition)) {

			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

				SceneManager::GetInstance()->LoadScene(L"Pick_Battle");
				return;
			}
		}

		mToggleButton(1, "HomeToBattle");
	}


}

void HomeToBattle::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 463, 245);

	}

}

void HomeToBattle::LoadFromFile(const string& fileName)
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


		for (int i = 0; i < v.size(); i += 4) {
			RECT rc = { v[i], v[i + 1], v[i + 2], v[i + 3] };
			mButtonList.push_back(rc);
		}

	}

	fin.close();
}

void HomeToBattle::mToggleButton(int index, string UIName)
{
	if (PtInRect(&mButtonList[index], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			GameObject* hptr = ObjectManager::GetInstance()->FindObject(UIName);
			hptr->SetIsActive(!hptr->GetIsActive());
		}
	}
}