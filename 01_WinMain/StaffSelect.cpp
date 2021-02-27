#include "pch.h"
#include "StaffSelect.h"
#include "Staff.h"
#include "Director.h"
#include "Champ.h"

StaffSelect::StaffSelect()
	: UI("StaffSelect")
{
	mIsActive = false;
}

void StaffSelect::Init()
{
	LoadFromFile("staffSelect"); // ?? 이거 왜 소문자임 취향인가 ??

	startX = mButtonList[50].left;
	startY = mButtonList[50].top;

	IMAGEMANAGER->LoadFromFile(L"BlueSelect", Resources(L"StaffSelect_blue.bmp"), 1080, 560, true);
	IMAGEMANAGER->LoadFromFile(L"RedSelect", Resources(L"StaffSelect_red.bmp"), 1080, 560, true);
	mImage = IMAGEMANAGER->FindImage(L"BlueSelect"); 

	player = (Director*)ObjectManager::GetInstance()->FindObject("Director1"); 
	enemy = ScheduleManager::GetInstance()->GetEnemy(player->GetWeek()); 

}

void StaffSelect::Release()
{
}

void StaffSelect::Update()
{
	if (mIsActive)
	{
	//-
		if (BData->GetPlayerTeam() == Team::Blue)//이러면 이미지 바뀔듯, 서순+
			mImage = IMAGEMANAGER->FindImage(L"BlueSelect");
		else if (BData->GetPlayerTeam() == Team::Red)
			mImage = IMAGEMANAGER->FindImage(L"RedSelect");





	//-
	//	if ()
		{
			//밴픽으로 이동
			if (Input::GetInstance()->GetKeyDown('F'))
			{
				ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(false);
				ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(true);
				ObjectManager::GetInstance()->FindObject("BanPickGuide")->SetIsActive(true);
				ObjectManager::GetInstance()->FindObject("ChampSelect")->SetIsActive(true);
				ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(true);
			}
			mToggleButton(51, "StaffSelect", []() 
				{
					ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(true); 
					ObjectManager::GetInstance()->FindObject("BanPickGuide")->SetIsActive(true);
					ObjectManager::GetInstance()->FindObject("ChampSelect")->SetIsActive(true);
					ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(true);
				}
			);	//다음버튼... 자기자신은 false로 하고 다음걸 true
		}
	}
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{

		mImage->Render(hdc, startX, startY);
		MouseOver(hdc);
		//우리팀 player







		//상대팀부터 출력해 볼까? enemy
		//상대 팀 마크 출력
		enemy->UIRender(hdc, 725 + startX, 100 + startY, 42, 42, false);
		
		//상대 팀 이름 출력
		wstring enemyTName = enemy->GetTeamName();
		CallFont(hdc, 30, [hdc, this, enemyTName]() {TextOut(hdc, 820 + startX, 105 + startY, enemyTName.c_str(), enemyTName.size()); });

		//상대 팀 리스트 로드
		vector <Staff*> enemyStaff= BData->GetEnemyStaff();

		auto func = [hdc, this, enemyStaff](int x, int y, int i)
		{
			//상대 선수 i번 이름
			wstring enemyStaffName = StoW(enemyStaff[i]->GetStaffName());
			CallFont(hdc, 30, [hdc, this, enemyStaffName,x,y]() {TextOut(hdc, 726 + startX+x, 155 + startY+y, enemyStaffName.c_str(), enemyStaffName.size()); });

			//상대 선수 i번 컨디션
			enemyStaff[i]->ConditionRender(hdc, startX + 849+x, startY + 156+y, 34, 29);

			//상대 선수 i번 얼굴
			enemyStaff[i]->UIRender(hdc, startX + x + 727, startY + y + 190, 52, 49);

			//상대 선수 i번 특성
			wstring enemyStaffChar = enemyStaff[i]->GetCharComment(1);
			CallFont(hdc, 15, [hdc, this, enemyStaffChar, x, y]() {TextOut(hdc, 815 + startX + x, 197 + startY + y, enemyStaffChar.c_str(), enemyStaffChar.size()); });

			//상대 선수 i번 공격력
			wstring enemyStaffAtk = to_wstring(enemyStaff[i]->GetAtk());
			CallFont(hdc, 17, [hdc, this, enemyStaffAtk, x, y]() {TextOut(hdc, 757 + startX + x, 244 + startY + y, enemyStaffAtk.c_str(), enemyStaffAtk.size()); });

			//상대 선수 i번 방어력
			wstring enemyStaffDef = to_wstring(enemyStaff[i]->GetDef());
			CallFont(hdc, 17, [hdc, this, enemyStaffDef, x, y]() {TextOut(hdc, 831 + startX + x, 244 + startY + y, enemyStaffDef.c_str(), enemyStaffDef.size()); });

			auto list = enemyStaff[i]->GetMostChamp();
			//상대 선수 i번 모스트1
			CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake(startX + x + 730, startY + y + 270, 35,35));});
			Champ* most1 = (Champ*)ObjectManager::GetInstance()->FindObject(list.begin()->first);
			most1->UIRender(hdc, startX + x + 730, startY + y + 270, 35, 35);
			RECT ptBox1 = RectMake(startX + x + 750, startY + y + 270, 15, 15);
			CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox1, x, y]() {RenderRect(hdc, ptBox1);});
			wstring most1Pt = to_wstring(list.begin()->second);
			CallFont(hdc, 15, [hdc, this, most1Pt, &ptBox1, x, y]() {DrawText(hdc, most1Pt.c_str(), most1Pt.size(), &ptBox1, DT_VCENTER|DT_SINGLELINE|DT_CENTER);});

			//상대 선수 i번 모스트2
			CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake(startX + x + 770, startY + y + 270, 35, 35));});
			Champ* most2 = (Champ*)ObjectManager::GetInstance()->FindObject(list.rbegin()->first);
			most2->UIRender(hdc, startX + x + 770, startY + y + 270, 35, 35);
			RECT ptBox2 = RectMake(startX + x + 790, startY + y + 270, 15, 15);
			CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox2, x, y]() {RenderRect(hdc, ptBox2);});
			wstring most2Pt = to_wstring(list.rbegin()->second);
			CallFont(hdc, 15, [hdc, this, most2Pt, &ptBox2, x, y]() {DrawText(hdc, most2Pt.c_str(), most2Pt.size(), &ptBox2, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});


		};

		func(0,0,0);
		func(171, 0,1);
		func(0, 164,2);

	}
}
