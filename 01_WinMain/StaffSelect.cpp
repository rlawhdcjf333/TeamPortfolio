#include "pch.h"
#include "StaffSelect.h"
#include "Staff.h"
#include "Director.h"

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

	//여기서 Director의 team?을 받아서 해당 색깔의 이미지를 Load/Find // Director의 팀을  UI init이 돌고 난 다음에 설정하므로 그건 불가능 따라서 이미지 설정 함수를 빼주...<-이걸 위해GetPlayerTeam함수를 만들었다
	IMAGEMANAGER->LoadFromFile(L"BlueSelect", Resources(L"StaffSelect_blue.bmp"), 1080, 560, true);
	IMAGEMANAGER->LoadFromFile(L"RedSelect", Resources(L"StaffSelect_red.bmp"), 1080, 560, true);
	mImage = IMAGEMANAGER->FindImage(L"BlueSelect"); //신에서 재설정하겠지만 그래도 초기화 하는 습관은 좋구요, 걱정 ㄴ 버그나면 어썰트로 막아둠

	player = (Director*)ObjectManager::GetInstance()->FindObject("Director1"); //플레이어 팀 포인터 저장
	enemy = ScheduleManager::GetInstance()->GetEnemy(player->GetWeek()); // 상대방 팀 포인터 저장

}

void StaffSelect::Release()
{
}

void StaffSelect::Update()
{
	if (mIsActive)
	{
	//-
		if (BData->GetPlayerTeam() == Team::Blue)//이러면 이미지 바뀔듯, 라운드가 돌고 돌아오면 거긴 Init이 안도니 여기서 바꿈
			mImage = IMAGEMANAGER->FindImage(L"BlueSelect");
		if (BData->GetPlayerTeam() == Team::Red)
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
				ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(true);
			}
			mToggleButton(51, "StaffSelect", []() 
				{
					ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(true); 
					ObjectManager::GetInstance()->FindObject("BanPickGuide")->SetIsActive(true);
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
		//우리팀 player





		//상대팀부터 출력해 볼까? enemy
		//상대 팀 마크 출력
		enemy->UIRender(hdc, 735 + startX, 100 + startY, 45, 45);
		
		//상대 팀 이름 출력
		wstring enemyTName = enemy->GetTeamName();
		CallFont(hdc, 40, [hdc, this, enemyTName]() {TextOut(hdc, 820 + startX, 100 + startY, enemyTName.c_str(), enemyTName.size()); });

		//상대 팀 리스트 로드
		vector <Staff*> enemyStaff; 
		enemyStaff.assign(BData->GetEnemyStaff().begin(), BData->GetEnemyStaff().end());

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
			CallFont(hdc, 15, [hdc, this, enemyStaffChar, x, y]() {TextOut(hdc, 811 + startX + x, 197 + startY + y, enemyStaffChar.c_str(), enemyStaffChar.size()); });

			//상대 선수 i번 공격력
			wstring enemyStaffAtk = to_wstring(enemyStaff[i]->GetAtk());
			CallFont(hdc, 17, [hdc, this, enemyStaffAtk, x, y]() {TextOut(hdc, 757 + startX + x, 246 + startY + y, enemyStaffAtk.c_str(), enemyStaffAtk.size()); });

			//상대 선수 i번 방어력
			wstring enemyStaffDef = to_wstring(enemyStaff[i]->GetDef());
			CallFont(hdc, 17, [hdc, this, enemyStaffDef, x, y]() {TextOut(hdc, 831 + startX + x, 246 + startY + y, enemyStaffDef.c_str(), enemyStaffDef.size()); });

		};

		func(0,0,0);
		func(171, 0,1);
		func(0, 166,2);

	}
}
