#include "pch.h"
#include "BattleUI.h"
#include "Staff.h"
#include "Champ.h"
#include "Director.h"

BattleUI::BattleUI() : UI("BattleUI")
{
	mIsActive = false;
}

void BattleUI::Init()
{
	IMAGEMANAGER->LoadFromFile(L"BattleUI", Resources(L"battleUI.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleUI");
	
	mTime = 60;
	mDeltaTime = 0.f;

	mPlayer = (Director*)ObjectManager::GetInstance()->FindObject("Director1");
	mEnemy = (Director*)ScheduleManager::GetInstance()->GetEnemy(mPlayer->GetWeek());

}

void BattleUI::Release()
{
}

void BattleUI::Update()
{
	if (!mIsActive)
	{
		return;
	}


	if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive())
	{
		if (mTime == 0 || Input::GetInstance()->GetKeyDown('G'))
		{
			//time == 0�϶� ų���� ���ؼ� ų�� ������ ���� �� ��� �¸�, ��ȸ?�� 2�����ϸ� �¸� //������ ��𰡽�
			ObjectManager::GetInstance()->FindObject("Battle")->SetIsActive(false);
			ObjectManager::GetInstance()->FindObject("BattleResult")->SetIsActive(true);
			return;
		}
		mDeltaTime += Time::GetInstance()->DeltaTime();//��ŸŸ�� = 1�������� ���� �ð�, 1�ʸ� ���Ϸ���? // ���� ���´� 1�ʿ� 1�� �ö�
		if (mDeltaTime >= 1)
		{
			mDeltaTime = 0.f;
			mTime -= 1;
		}
	}
	else
	{
		mTime = 60;
	}
}

void BattleUI::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);






		StaffInfoRender(hdc);

		if (ObjectManager::GetInstance()->FindObject("Battle")->GetIsActive())	//��Ʋ���϶�
		{
			TextOut(hdc, 640, 60, to_wstring(mTime).c_str(), to_wstring(mTime).size());
		}
	}
}

void BattleUI::StaffInfoRender(HDC hdc)
{
	if (BData->GetPlayerTeam() == Team::Blue)
	{
		vector <Staff*> myTeam;
		myTeam.emplace_back(BData->GetSelectStaff(0));
		myTeam.emplace_back(BData->GetSelectStaff(1));
		myTeam.emplace_back(BData->GetSelectStaff(2));

		DrawStaff(hdc, 3, 80, myTeam, 0);
		DrawStaff(hdc, 3, 240, myTeam, 1);
		DrawStaff(hdc, 3, 400, myTeam, 2);

		vector <Staff*> enemyTeam;
		enemyTeam = BData->GetEnemyStaff();

		DrawStaff(hdc, 1125, 80, enemyTeam, 0);
		DrawStaff(hdc, 1125, 240, enemyTeam, 1);
		DrawStaff(hdc, 1125, 400, enemyTeam, 2);
	}
	else if (BData->GetPlayerTeam() == Team::Red)
	{
		vector <Staff*> myTeam;
		myTeam.emplace_back(BData->GetSelectStaff(0));
		myTeam.emplace_back(BData->GetSelectStaff(1));
		myTeam.emplace_back(BData->GetSelectStaff(2));

		DrawStaff(hdc, 1125, 80, myTeam, 0);
		DrawStaff(hdc, 1125, 240, myTeam, 1);
		DrawStaff(hdc, 1125, 400, myTeam, 2);

		vector <Staff*> enemyTeam;
		enemyTeam = BData->GetEnemyStaff();

		DrawStaff(hdc, 3, 80, enemyTeam, 0);
		DrawStaff(hdc, 3, 240, enemyTeam, 1);
		DrawStaff(hdc, 3, 400, enemyTeam, 2);

	}


}

void BattleUI::DrawStaff(HDC hdc, int x, int y, vector<Staff*> list, int i)
{
	//���� i�� �̸�
	wstring enemyStaffName = StoW(list[i]->GetStaffName());
	CallFont(hdc, 30, [hdc, this, enemyStaffName, x, y]() {TextOut(hdc, x, y, enemyStaffName.c_str(), enemyStaffName.size()); });

	//���� i�� �����
	list[i]->ConditionRender(hdc, 123 + x, 1 + y, 34, 29);

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
	CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake(x + 4, y + 115, 35, 35));});
	Champ* most1 = (Champ*)ObjectManager::GetInstance()->FindObject(champList.begin()->first);
	most1->UIRender(hdc, x + 4, y + 115, 35, 35);
	RECT ptBox1 = RectMake(x + 24, y + 115, 15, 15);
	CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox1, x, y]() {RenderRect(hdc, ptBox1);});
	wstring most1Pt = to_wstring(champList.begin()->second);
	CallFont(hdc, 15, [hdc, this, most1Pt, &ptBox1, x, y]() {DrawText(hdc, most1Pt.c_str(), most1Pt.size(), &ptBox1, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});

	//���� i�� ��Ʈ2
	CallBrush(hdc, RGB(33, 35, 39), [hdc, this, x, y]() {RenderRect(hdc, RectMake(x + 44, y + 115, 35, 35));});
	Champ* most2 = (Champ*)ObjectManager::GetInstance()->FindObject(champList.rbegin()->first);
	most2->UIRender(hdc, x + 44, y + 115, 35, 35);
	RECT ptBox2 = RectMake(x + 64, y + 115, 15, 15);
	CallBrush(hdc, RGB(11, 13, 17), [hdc, this, ptBox2, x, y]() {RenderRect(hdc, ptBox2);});
	wstring most2Pt = to_wstring(champList.rbegin()->second);
	CallFont(hdc, 15, [hdc, this, most2Pt, &ptBox2, x, y]() {DrawText(hdc, most2Pt.c_str(), most2Pt.size(), &ptBox2, DT_VCENTER | DT_SINGLELINE | DT_CENTER);});

}

void BattleUI::TeamRender(HDC hdc)
{
	if (BData->GetPlayerTeam() == Team::Blue)
	{

		







	}



}
