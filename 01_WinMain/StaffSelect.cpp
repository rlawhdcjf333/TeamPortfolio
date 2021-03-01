#include "pch.h"
#include "Staff.h"
#include "Director.h"
#include "Champ.h"
#include "Child.h"

StaffSelect::StaffSelect()
	: UI("StaffSelect")
{
	mIsActive = false;
}

void StaffSelect::Init()
{
	LoadFromFile("staffSelect2"); // ?? �̰� �� �ҹ����� �����ΰ� ??


	IMAGEMANAGER->LoadFromFile(L"BlueSelect", Resources(L"StaffSelect_blue.bmp"), 1080, 560, true);
	IMAGEMANAGER->LoadFromFile(L"RedSelect", Resources(L"StaffSelect_red.bmp"), 1080, 560, true);
	mImage = IMAGEMANAGER->FindImage(L"BlueSelect"); 

	player = (Director*)ObjectManager::GetInstance()->FindObject("Director1"); 
	enemy = ScheduleManager::GetInstance()->GetEnemy(player->GetWeek()); 

	firstClick = nullptr;
	secondClick = nullptr;

}

void StaffSelect::Release()
{
}

void StaffSelect::Update()
{
	if (mIsActive)
	{
	//-
		if (BData->GetPlayerTeam() == Team::Blue)
		{
			mImage = IMAGEMANAGER->FindImage(L"BlueSelect");
		}
		else if (BData->GetPlayerTeam() == Team::Red)
		{
			mImage = IMAGEMANAGER->FindImage(L"RedSelect");
		}

		//���� ���� ����
		mToggleButton(0, "None", [this]()
			{
				firstClick = BData->GetSelectStaff(0);
				firstClickRect = mButtonList[0];
			}
		);
		mToggleButton(1, "None", [this]()
			{
				firstClick = BData->GetSelectStaff(1);
				firstClickRect = mButtonList[1];
			}
		);
		mToggleButton(2, "None", [this]()
			{
				firstClick = BData->GetSelectStaff(2);
				firstClickRect = mButtonList[2];
			}
		);

		//��� ���� ����
		if (BData->GetWaitStaff(0))
		{
			mToggleButton(3, "None", [this]()
				{
					secondClick = BData->GetWaitStaff(0);
					secondClickRect = mButtonList[3];
				}
			);
		}
		if (BData->GetWaitStaff(1))
		{
			mToggleButton(4, "None", [this]()
				{
					secondClick = BData->GetWaitStaff(1);
					secondClickRect = mButtonList[4];
				}
			);
		}



		//���� �Ϸ�Ǹ� �����ϰ� ���� ĳ�� ����
		if (firstClick != nullptr and secondClick != nullptr)
		{
			BData->StaffSwap(secondClick, firstClick);
			firstClick = nullptr;
			secondClick = nullptr;
		}



			//�������� �̵�
		if (Input::GetInstance()->GetKeyDown('F'))
		{
			ObjectManager::GetInstance()->FindObject("StaffSelect")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(true);
			ObjectManager::GetInstance()->FindObject("BanPickGuide")->SetIsActive(true);
			ChampSelect* hptr = (ChampSelect*)ObjectManager::GetInstance()->FindObject("ChampSelect");
			hptr->ClearCurrentChamp();
			hptr->SetIsActive(true);
			ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(true);
		}
		mToggleButton(5, "StaffSelect", []() 
			{
				ObjectManager::GetInstance()->FindObject("BanPick")->SetIsActive(true); 
				ObjectManager::GetInstance()->FindObject("BanPickGuide")->SetIsActive(true);
				ObjectManager::GetInstance()->FindObject("ChampSelect")->SetIsActive(true);
				ObjectManager::GetInstance()->FindObject("BattleUI")->SetIsActive(true);
			}
		);	//������ư... �ڱ��ڽ��� false�� �ϰ� ������ true
	}
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{

		mImage->Render(hdc, 97, 79);
		MouseOver(hdc);

		//���� ��Ȳ ǥ��
		if(firstClick) CallEdge(hdc, firstClickRect);
		if(secondClick) CallEdge(hdc, secondClickRect);


		//�츮�� player ���� ����Ʈ
		vector <Staff*> selectStaff; 
		selectStaff.emplace_back(BData->GetSelectStaff(0)); //emplace_back:: ���ɻ� ����
		selectStaff.emplace_back(BData->GetSelectStaff(1));
		selectStaff.emplace_back(BData->GetSelectStaff(2));

		//�츮�� ���� ���
		DrawStaff(hdc, 128, 234, selectStaff, 0);
		DrawStaff(hdc, 128+171, 234, selectStaff, 1);
		DrawStaff(hdc, 128, 164+234, selectStaff, 2);

		//�츮�� ��� ����Ʈ
		vector <Staff*> waitStaff;
		if (BData->GetWaitStaff(0) != nullptr) waitStaff.emplace_back(BData->GetWaitStaff(0));
		if (BData->GetWaitStaff(1) != nullptr) waitStaff.emplace_back(BData->GetWaitStaff(1));

		//�츮�� ��� ���

		if (waitStaff.size() >= 1) DrawStaff(hdc, 606, 234, waitStaff, 0);
		if (waitStaff.size() >= 2) DrawStaff(hdc, 606, 234 + 164, waitStaff, 1);



		//��� �� ��ũ ���
		enemy->UIRender(hdc, 725 + 97, 100 + 79, 42, 42, false);
		
		//��� �� �̸� ���
		wstring enemyTName = enemy->GetTeamName();
		CallFont(hdc, 30, [hdc, this, enemyTName]() {TextOut(hdc, 820 + 97, 105 + 79, enemyTName.c_str(), enemyTName.size()); });

		//��� �� ����Ʈ �ε�
		vector <Staff*> enemyStaff= BData->GetEnemyStaff();

		//��� �� ���
		DrawStaff(hdc, 823, 234, enemyStaff, 0);
		DrawStaff(hdc, 823+171, 234, enemyStaff, 1);
		DrawStaff(hdc, 823, 234+164, enemyStaff, 2);


	}
}

void StaffSelect::DrawStaff(HDC hdc, int x, int y, vector<Staff*> list, int i)
{
	//���� i�� �̸�
	wstring enemyStaffName = StoW(list[i]->GetStaffName());
	CallFont(hdc, 30, [hdc, this, enemyStaffName, x, y]() {TextOut(hdc, x, y, enemyStaffName.c_str(), enemyStaffName.size()); });

	//���� i�� �����
	list[i]->ConditionRender(hdc, 123 + x, 1+ y, 34, 29);

	//���� i�� ��
	list[i]->UIRender(hdc, x + 1, y + 35, 52, 49);

	//���� i�� Ư��
	wstring enemyStaffChar = list[i]->GetCharComment(1);
	CallFont(hdc, 15, [hdc, this, enemyStaffChar, x, y]() {TextOut(hdc, 89 + x, 42 + y, enemyStaffChar.c_str(), enemyStaffChar.size()); });

	//���� i�� ���ݷ�
	wstring enemyStaffAtk = to_wstring(list[i]->GetAtk());
	CallFont(hdc, 17, [hdc, this, enemyStaffAtk, x, y]() {TextOut(hdc, 31 + x, 89 + y, enemyStaffAtk.c_str(), enemyStaffAtk.size()); });

	//���� i�� ����
	wstring enemyStaffDef = to_wstring(list[i]->GetDef());
	CallFont(hdc, 17, [hdc, this, enemyStaffDef, x, y]() {TextOut(hdc, 105 + x, 89 + y, enemyStaffDef.c_str(), enemyStaffDef.size()); });

	auto champList = list[i]->GetMostChamp();
	//���� i�� ��Ʈ1
	CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake( x + 4, y + 115, 35, 35));});
	Champ* most1 = (Champ*)ObjectManager::GetInstance()->FindObject(champList.begin()->first);
	most1->UIRender(hdc,  x + 4,  y + 115, 35, 35);
	RECT ptBox1 = RectMake(x + 24, y + 115, 15, 15);
	CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox1, x, y]() {RenderRect(hdc, ptBox1);});
	wstring most1Pt = to_wstring(champList.begin()->second);
	CallFont(hdc, 15, [hdc, this, most1Pt, &ptBox1, x, y]() {DrawText(hdc, most1Pt.c_str(), most1Pt.size(), &ptBox1, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});

	//���� i�� ��Ʈ2
	CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake( x + 44,  y + 115, 35, 35));});
	Champ* most2 = (Champ*)ObjectManager::GetInstance()->FindObject(champList.rbegin()->first);
	most2->UIRender(hdc, x + 44, y + 115, 35, 35);
	RECT ptBox2 = RectMake( x + 64, y + 115, 15, 15);
	CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox2, x, y]() {RenderRect(hdc, ptBox2);});
	wstring most2Pt = to_wstring(champList.rbegin()->second);
	CallFont(hdc, 15, [hdc, this, most2Pt, &ptBox2, x, y]() {DrawText(hdc, most2Pt.c_str(), most2Pt.size(), &ptBox2, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});

}
