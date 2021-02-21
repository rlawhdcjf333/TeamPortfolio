#include "pch.h"
#include "ChampInfo.h"

ChampInfo::ChampInfo()
	:GameObject("ChampInfo")
{
	mIsActive = false;
}

void ChampInfo::Init()
{
	LoadFromFile("ChampInfo");

	IMAGEMANAGER->LoadFromFile(L"ChampInfo", Resources(L"ChampInfo.bmp"), 1247, 552, true);
	mImage = IMAGEMANAGER->FindImage(L"ChampInfo");
	
}

void ChampInfo::Release()
{
}

void ChampInfo::Update()
{
	if (mIsActive)
	{

		mToggleButton(6, "ChampInfo");
	}

}

void ChampInfo::Render(HDC hdc)
{

	if (mIsActive)
	{
		mImage->Render(hdc, 18,55);
	}

}

void ChampInfo::mToggleButton(int index, string UIName, function <void(void)> func)
{
	if (PtInRect(&mButtonList[index], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			GameObject* hptr = ObjectManager::GetInstance()->FindObject(UIName);
			hptr->SetIsActive(!hptr->GetIsActive());

			func();

		}
	}
}

void ChampInfo::LoadFromFile(const string& fileName)
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
