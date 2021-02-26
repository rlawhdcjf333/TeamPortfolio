#include "pch.h"
#include "BattleData.h"
#include "Director.h"
void BattleData::SetTeam(Team t, Director * dir)
{
	switch (t)
	{
	case Team::Blue:
		mBlueTeam.mDirector = dir;
		LoadStaffList(mBlueTeam);
		mBlueTeam.mKillCount = 0;
		mBlueTeam.mWinCount = 0;
		break;
	case Team::Red:
		mRedTeam.mDirector = dir;
		LoadStaffList(mRedTeam);
		mRedTeam.mKillCount = 0;
		mRedTeam.mWinCount = 0;
		break;
	}
}
void BattleData::LoadStaffList(TeamData t)
{
	t.mStaffList.clear();
	t.mStaffList.shrink_to_fit();

	auto list = t.mDirector->GetStaffNameList();

	for (string elem : list)
	{
		if (ObjectManager::GetInstance()->FindObject(elem) != nullptr)
		{
			Staff* temp = (Staff*)ObjectManager::GetInstance()->FindObject(elem);
			t.mStaffList.push_back(temp);
		}

	}

	for (int i; i < t.mStaffList.size(); ++i)//�迭�̴� ���� �ʱ�ȭ�Ҷ� �Ⱥ���൵��
	{
		if (i < 3)
			t.mSelectStaff[i] = t.mStaffList[i];
		else if(i >= 3 && i < 5)
			t.mWaitStaff[i] = t.mStaffList[i];
	}
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

void BattleData::Peedback()
{
	//������ư�� ������ ���� ����� �������̶� �ƽ��� ��� �ϴ°� ������...
}
