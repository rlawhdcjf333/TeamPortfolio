#include "pch.h"
#include "BattleData.h"
#include "Director.h"
#include "Staff.h"
#include "StaffSelect.h"

void BattleData::RoundReset()
{
	mSelectChamp.clear();
	mBanChamp[0] = nullptr;
	mBanChamp[1] = nullptr;
}

void BattleData::SetTeam(Team t, Director * dir)
{
	switch (t)
	{
	case Team::Blue:
		mBlueTeam.mDirector = dir;
		mBlueTeam = LoadStaffList(dir);
		break;
	case Team::Red:
		mRedTeam.mDirector = dir;
		mRedTeam = LoadStaffList(dir);
		break;
	}
}

TeamData BattleData::LoadStaffList(Director* dir)
{
	 TeamData t ;
	//t.mStaffList.clear();
	//t.mStaffList.shrink_to_fit();
	 t.mDirector = dir;


	vector<string> list = dir->GetStaffNameList();

	for (string elem : list)
	{
		if (ObjectManager::GetInstance()->FindObject(elem) != nullptr)
		{
			Staff* temp = (Staff*)ObjectManager::GetInstance()->FindObject(elem);
			t.mStaffList.push_back(temp);
		}

	}

	for (int i = 0; i < t.mStaffList.size(); ++i)//�迭�̴� ���� �ʱ�ȭ�Ҷ� �Ⱥ���൵��
	{
		if (i < 3)
			t.mSelectStaff[i] = t.mStaffList[i];
		else if(i > 3 && i < 5)
			t.mWaitStaff[i-3] = t.mStaffList[i];
	}
	t.mKillCount = 0;
	t.mWinCount = 0;

	Staff* tempo = t.mSelectStaff[0];
	Staff* tempoi = t.mSelectStaff[1];
	Staff* tempoiu = t.mSelectStaff[2];

	return t;
}

void BattleData::StaffSwap(Staff * waittoselect, Staff * selecttowait)
{
	switch (mPlayerTeam)
	{
	case Team::Blue:
		for (int i = 0; i < 3; ++i)
		{
			if (mBlueTeam.mSelectStaff[i] == selecttowait)
				mBlueTeam.mSelectStaff[i] = waittoselect;
			break;
		}
		for (int i = 0; i < 2; ++i)
		{
			if (mBlueTeam.mWaitStaff[i] == waittoselect)
				mBlueTeam.mWaitStaff[i] = selecttowait;
			break;
		}
		break;
	case Team::Red:
		for (int i = 0; i < 3; ++i)
		{
			if (mRedTeam.mSelectStaff[i] == selecttowait)
				mRedTeam.mSelectStaff[i] = waittoselect;
			break;
		}
		for (int i = 0; i < 2; ++i)
		{
			if (mRedTeam.mWaitStaff[i] == waittoselect)
				mRedTeam.mWaitStaff[i] = selecttowait;
			break;
		}
		break;
	} 
}

void BattleData::ChampBan(Champ * ban)
{
	for (int i = 0; i < 2; ++i)
	{
		if (!mBanChamp[i])	//nullptr�� �ƴϸ�
		{
			mBanChamp[i] = ban;
			return;
		}
	}
}

bool BattleData::ChampSelect(Staff * st, Champ * c)
{
	if (mSelectChamp.find(st) == mSelectChamp.end())
	{
		mSelectChamp.insert(make_pair(st, c));
		return true;
	}

	return false;
}

void BattleData::ChampSwap(Staff * st1, Staff * st2)
{
	//�÷��̾��� selectstaff���� Ȯ��(Ȥ�� ���� ����)
	bool checkMyTeam = false;
	switch (mPlayerTeam)
	{
	case Team::Blue:
		for (int i = 0; i < 3; ++i)
		{
			if (mBlueTeam.mSelectStaff[i] == st1)
			{
				checkMyTeam = true;
				break;//for
			}
			checkMyTeam = false;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (mBlueTeam.mSelectStaff[i] == st2)
			{
				checkMyTeam = true;
				break;//for
			}
			checkMyTeam = false;
		}
		break;//case blue
	case Team::Red:
		for (int i = 0; i < 3; ++i)
		{
			if (mRedTeam.mSelectStaff[i] == st1)
			{
				checkMyTeam = true;
				break;//for
			}
			checkMyTeam = false;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (mRedTeam.mSelectStaff[i] == st2)
			{
				checkMyTeam = true;
				break;//for
			}
			checkMyTeam = false;
		}
		break;//case red
	}
	if (!checkMyTeam)//�ϳ��� �÷��̾��� ���������� �ƴ϶��
		return;

	//Ȯ���� �������� ����
	Champ* temp;
	temp = mSelectChamp.find(st1)->second;
	mSelectChamp.find(st1)->second = mSelectChamp.find(st2)->second;
	mSelectChamp.find(st2)->second = temp;
}

void BattleData::Feedback(int i)//i = ��ư ��ȣ(1~4)
{
	//��ư���� ���ڸ� �����ؼ� �Լ��� ȣ��
	int con = 0;
	switch (mPlayerTeam)
	{
	case Team::Blue:
		switch (i)
		{
		case 1:
			if (mBlueTeam.mWinCount >= mRedTeam.mWinCount)
				con = 1;
			else
				con = -1;
			break;
		case 2:
			if (mBlueTeam.mWinCount >= mRedTeam.mWinCount)
				con = Random::GetInstance()->RandomInt(0, 1);
			else
				con = Random::GetInstance()->RandomInt(0, 2) - 1;
			break;
		case 3:
			if (mBlueTeam.mWinCount >= mRedTeam.mWinCount)
				con = Random::GetInstance()->RandomInt(0, 2) - 1;
			else
				con = 1;
			break;
		case 4: default:
			if (mBlueTeam.mWinCount >= mRedTeam.mWinCount)
				con = Random::GetInstance()->RandomInt(0, 1) - 2;
			else
				con = Random::GetInstance()->RandomInt(0, 4);
			break;
		}//i
		UpdateCondition(mBlueTeam, con);
		break;//case blue
	case Team::Red:
		switch (i)
		{
		case 1:
			if (mBlueTeam.mWinCount <= mRedTeam.mWinCount)
				con = 1;
			else
				con = -1;
			break;
		case 2:
			if (mBlueTeam.mWinCount <= mRedTeam.mWinCount)
				con = Random::GetInstance()->RandomInt(0, 1);
			else
				con = Random::GetInstance()->RandomInt(0, 2) - 1;
			break;
		case 3:
			if (mBlueTeam.mWinCount <= mRedTeam.mWinCount)
				con = Random::GetInstance()->RandomInt(0, 2) - 1;
			else
				con = 1;
			break;
		case 4: default:
			if (mBlueTeam.mWinCount <= mRedTeam.mWinCount)
				con = Random::GetInstance()->RandomInt(0, 1) - 2;
			else
				con = Random::GetInstance()->RandomInt(0, 4);
			break;
		}//i
		UpdateCondition(mRedTeam, con);
		break;//case red
	}//mPlayerTeam
}

void BattleData::UpdateCondition(TeamData t,int con)
{
	for (int i = 0; i < t.mStaffList.size(); ++i)
	{
		int tcon = (int)t.mStaffList[i]->GetCondition();
		tcon += con;
		if (tcon < 0)
			tcon = 0;
		if (tcon > 4)
			tcon = 4;
		t.mStaffList[i]->SetCondition((Condition)tcon);
	}
}

void BattleData::SetResult()
{
	if (mBlueTeam.mWinCount > mRedTeam.mWinCount)//����� �¸�
	{
		mBlueTeam.mDirector->SetWin(mBlueTeam.mDirector->GetWin() + 1);
		mRedTeam.mDirector->SetLose(mRedTeam.mDirector->GetLose() + 1);
	}
	if (mBlueTeam.mWinCount < mRedTeam.mWinCount)//������ �¸�
	{
		mBlueTeam.mDirector->SetLose(mBlueTeam.mDirector->GetLose() + 1);
		mRedTeam.mDirector->SetWin(mRedTeam.mDirector->GetWin() + 1);
	}
}

void BattleData::SetStaffSelect()
{
	StaffSelect* tmp = (StaffSelect*)ObjectManager::GetInstance()->FindObject("StaffSelect");

	if (mPlayerTeam == Team::Blue)
	{
		tmp->SetImage(IMAGEMANAGER->FindImage(L"BlueSelect"));
	}
	else if(mPlayerTeam==Team::Red)
	{
		tmp->SetImage(IMAGEMANAGER->FindImage(L"RedSelect"));
	}
	else
	{
		wstring alert = L"�÷��̾� ���� �������� �ʾҰų� �߸��� ���� �����Ǿ����ϴ�.";
		wstring caption = L"����!";
		MessageBox(_hWnd, alert.c_str(), caption.c_str(), MB_OK);
		assert(false);
		
	}
}

vector<Staff*> BattleData::GetEnemyStaff()
{
	vector <Staff*> result;

	if (mPlayerTeam == Team::Blue)
	{
		result.push_back(mRedTeam.mStaffList[0]);
		result.push_back(mRedTeam.mStaffList[1]);
		result.push_back(mRedTeam.mStaffList[2]);
	}
	else if (mPlayerTeam == Team::Red)
	{
		result.push_back(mBlueTeam.mStaffList[0]);
		result.push_back(mBlueTeam.mStaffList[1]);
		result.push_back(mBlueTeam.mStaffList[2]);
	}

	return result;
}

void BattleData::TeamChange()
{
	//�ٲܰ� mPlayerTeam,mBlueTeam<->mRedTeam
	if (mPlayerTeam == Team::Blue)	//mPlayerTeam : �Լ� ������ �� �ĺ������� ���̴� ���� ����
		mPlayerTeam = Team::Red;
	else if (mPlayerTeam == Team::Red)	//else if <- �� �� �ϳ��� ����Ǿ��ؼ�
		mPlayerTeam = Team::Blue;

	TeamData temp = mBlueTeam;	//temp�� ����� ������ ����
	mBlueTeam = mRedTeam;	//������ �����͸� ��������� ����
	mRedTeam = temp;		//temp(����� ���纻)�� ���������� ���� �ϸ� ������ �ư���?
}
