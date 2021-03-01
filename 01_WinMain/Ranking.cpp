#include "pch.h"
#include "Ranking.h"
#include "Director.h"

Ranking::Ranking()
	:UI("Ranking")
{
	mIsActive = false;
}

void Ranking::Init()
{
	LoadFromFile("Ranking");

	IMAGEMANAGER->LoadFromFile(L"Ranking", Resources(L"Ranking.bmp"), WINSIZEX, WINSIZEY, true);
	mImage = IMAGEMANAGER->FindImage(L"Ranking");

	LoadDirectorList();
}

void Ranking::Release()
{

}

void Ranking::Update()
{
	if (mIsActive) {
		ObjectManager::GetInstance()->FindObject("TeamToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("GameToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("HomeToBattle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("LeagueToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("OperationToggle")->SetIsActive(false);
		ObjectManager::GetInstance()->FindObject("SystemToggle")->SetIsActive(false);

		mToggleButton(0, "Ranking");
	}
}

void Ranking::Render(HDC hdc)
{
	if (mIsActive) {

		function <bool(Director* a, Director* b)> funcc = [](Director* a, Director* b)
		{
			if (a->GetLeagueScore() == b->GetLeagueScore())
			{
				return a->GetName() < b->GetName();
			}
			return a->GetLeagueScore() > b->GetLeagueScore();
		};
		sort(mDirectorList.begin(), mDirectorList.end(), funcc);

		vector<RECT> largeBox;
		vector<RECT> smallBox; // 랭킹 숫자 들어갈 랙트
		vector<RECT> teamNameBox;
		vector<RECT> teamScoreBox;
		vector<RECT> teamKillBox;
		vector<RECT> teamDeathBox;

		mImage->Render(hdc, 0, 0);
		for (int i = 0; i < mDirectorList.size(); i++) {
			largeBox.push_back(RectMake(46, 181 + ( i * 74), 592, 64));
			smallBox.push_back(RectMake(46, 181 + ( i * 74), 64, 64));
			teamNameBox.push_back(RectMake(182, 188 + (i * 74), 250, 26));
			teamScoreBox.push_back(RectMake(182, 214 + (i * 74), 250, 26));
			teamKillBox.push_back(RectMake(436, 197 + (i * 74), 34, 34));
			teamDeathBox.push_back(RectMake(491, 197 + (i * 74), 34, 34));
		}

		for (int i = 0; i < mDirectorList.size(); i++) {
			wstring rank = to_wstring(mDirectorList[i]->GetRank());
			wstring teamName = mDirectorList[i]->GetTeamName();
			wstring teamScore = to_wstring(mDirectorList[i]->GetWin()) + L"승  " + 
				to_wstring(mDirectorList[i]->GetLose()) + L"패   +" + to_wstring(mDirectorList[i]->GetLeagueScore());
			wstring teamKill = to_wstring(mDirectorList[i]->GetTeamTotalKill());
			wstring teamDeath = to_wstring(mDirectorList[i]->GetTeamTotalDeath());

			HBRUSH newB = CreateSolidBrush(RGB(16, 18, 22));
			HBRUSH oldB = (HBRUSH) SelectObject(hdc, newB);
			RenderRect(hdc, largeBox[i]);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			newB = CreateSolidBrush(RGB(55, 57, 61));
			oldB = (HBRUSH)SelectObject(hdc, newB);
			RenderRect(hdc, smallBox[i]);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			mDirectorList[i]->TeamImageRender(hdc, 112, 182 + (i * 74.5), 60, 60);
			

			if (mDirectorList[i]->GetTeamName() == L"TeamNuguri")
				newB = CreateSolidBrush(RGB(241, 202, 92));
			else newB = CreateSolidBrush(RGB(255, 255, 255));
			oldB = (HBRUSH)SelectObject(hdc, newB);
			HFONT newF = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			HFONT oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, rank.c_str(), rank.length(), &smallBox[i], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);
			
			newF = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, teamName.c_str(), teamName.length(), &teamNameBox[i], DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);

			newF = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, teamScore.c_str(), teamScore.length(), &teamScoreBox[i], DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			newF = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			oldF = (HFONT)SelectObject(hdc, newF);
			DrawText(hdc, teamKill.c_str(), teamKill.length(), &teamKillBox[i], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			DrawText(hdc, teamDeath.c_str(), teamDeath.length(), &teamDeathBox[i], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			SelectObject(hdc, oldF);
			DeleteObject(newF);
			SelectObject(hdc, oldB);
			DeleteObject(newB);

			MouseOver(hdc);
		}
	}
}

void Ranking::LoadDirectorList()
{
	for (int i = 1; i < 5; i++) {
		mDirector = (Director*) ObjectManager::GetInstance()->FindObject("Director" + to_string(i));
		mDirectorList.push_back(mDirector);
	}
}