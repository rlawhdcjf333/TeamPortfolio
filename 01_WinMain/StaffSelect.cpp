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
	LoadFromFile("staffSelect"); // ?? �̰� �� �ҹ����� �����ΰ� ??

	startX = mButtonList[50].left;
	startY = mButtonList[50].top;

	//���⼭ Director�� team?�� �޾Ƽ� �ش� ������ �̹����� Load/Find // Director�� ����  UI init�� ���� �� ������ �����ϹǷ� �װ� �Ұ��� ���� �̹��� ���� �Լ��� ����...<-�̰� ����GetPlayerTeam�Լ��� �������
	IMAGEMANAGER->LoadFromFile(L"BlueSelect", Resources(L"StaffSelect_blue.bmp"), 1080, 560, true);
	IMAGEMANAGER->LoadFromFile(L"RedSelect", Resources(L"StaffSelect_red.bmp"), 1080, 560, true);
	mImage = IMAGEMANAGER->FindImage(L"BlueSelect"); //�ſ��� �缳���ϰ����� �׷��� �ʱ�ȭ �ϴ� ������ ������, ���� �� ���׳��� ���Ʈ�� ���Ƶ�

	player = (Director*)ObjectManager::GetInstance()->FindObject("Director1"); //�÷��̾� �� ������ ����
	enemy = ScheduleManager::GetInstance()->GetEnemy(player->GetWeek()); // ���� �� ������ ����

}

void StaffSelect::Release()
{
}

void StaffSelect::Update()
{
	if (mIsActive)
	{
	//-
		if (BData->GetPlayerTeam() == Team::Blue)//�̷��� �̹��� �ٲ��, ���尡 ���� ���ƿ��� �ű� Init�� �ȵ��� ���⼭ �ٲ�
			mImage = IMAGEMANAGER->FindImage(L"BlueSelect");
		if (BData->GetPlayerTeam() == Team::Red)
			mImage = IMAGEMANAGER->FindImage(L"RedSelect");





	//-
	//	if ()
		{
			//�������� �̵�
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
			);	//������ư... �ڱ��ڽ��� false�� �ϰ� ������ true
		}
	}
}

void StaffSelect::Render(HDC hdc)
{
	if (mIsActive)
	{


		mImage->Render(hdc, startX, startY);
		//�츮�� player





		//��������� ����� ����? enemy
		//��� �� ��ũ ���
		enemy->UIRender(hdc, 735 + startX, 100 + startY, 45, 45);
		
		//��� �� �̸� ���
		wstring enemyTName = enemy->GetTeamName();
		CallFont(hdc, 40, [hdc, this, enemyTName]() {TextOut(hdc, 820 + startX, 100 + startY, enemyTName.c_str(), enemyTName.size()); });

		//��� �� ����Ʈ �ε�
		vector <Staff*> enemyStaff; 
		enemyStaff.assign(BData->GetEnemyStaff().begin(), BData->GetEnemyStaff().end());

		auto func = [hdc, this, enemyStaff](int x, int y, int i)
		{
			//��� ���� i�� �̸�
			wstring enemyStaffName = StoW(enemyStaff[i]->GetStaffName());
			CallFont(hdc, 30, [hdc, this, enemyStaffName,x,y]() {TextOut(hdc, 726 + startX+x, 155 + startY+y, enemyStaffName.c_str(), enemyStaffName.size()); });

			//��� ���� i�� �����
			enemyStaff[i]->ConditionRender(hdc, startX + 849+x, startY + 156+y, 34, 29);

			//��� ���� i�� ��
			enemyStaff[i]->UIRender(hdc, startX + x + 727, startY + y + 190, 52, 49);

			//��� ���� i�� Ư��
			wstring enemyStaffChar = enemyStaff[i]->GetCharComment(1);
			CallFont(hdc, 15, [hdc, this, enemyStaffChar, x, y]() {TextOut(hdc, 811 + startX + x, 197 + startY + y, enemyStaffChar.c_str(), enemyStaffChar.size()); });

			//��� ���� i�� ���ݷ�
			wstring enemyStaffAtk = to_wstring(enemyStaff[i]->GetAtk());
			CallFont(hdc, 17, [hdc, this, enemyStaffAtk, x, y]() {TextOut(hdc, 757 + startX + x, 246 + startY + y, enemyStaffAtk.c_str(), enemyStaffAtk.size()); });

			//��� ���� i�� ����
			wstring enemyStaffDef = to_wstring(enemyStaff[i]->GetDef());
			CallFont(hdc, 17, [hdc, this, enemyStaffDef, x, y]() {TextOut(hdc, 831 + startX + x, 246 + startY + y, enemyStaffDef.c_str(), enemyStaffDef.size()); });

		};

		func(0,0,0);
		func(171, 0,1);
		func(0, 166,2);

	}
}
