#include "pch.h"
#include "BattleData.h"
#include "Director.h"
#include "Staff.h"

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

	for (int i = 0; i < t.mStaffList.size(); ++i)//배열이니 새로 초기화할때 안비워줘도댐
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
		if (!mBanChamp[i])	//nullptr이 아니면
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
	//플레이어의 selectstaff인지 확인(혹시 몰라서 만듬)
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
	if (!checkMyTeam)//하나라도 플레이어의 출전선수가 아니라면
		return;

	//확인이 끝났으니 스왑
	Champ* temp;
	temp = mSelectChamp.find(st1)->second;
	mSelectChamp.find(st1)->second = mSelectChamp.find(st2)->second;
	mSelectChamp.find(st2)->second = temp;
}

void BattleData::Feedback(int i)
{
	//버튼별로 숫자를 지정해서 함수를 호출
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
	if (mBlueTeam.mWinCount > mRedTeam.mWinCount)//블루팀 승리
	{
		mBlueTeam.mDirector->SetWin(mBlueTeam.mDirector->GetWin() + 1);
		mRedTeam.mDirector->SetLose(mRedTeam.mDirector->GetLose() + 1);
	}
	if (mBlueTeam.mWinCount < mRedTeam.mWinCount)//레드팀 승리
	{
		mBlueTeam.mDirector->SetLose(mBlueTeam.mDirector->GetLose() + 1);
		mRedTeam.mDirector->SetWin(mRedTeam.mDirector->GetWin() + 1);
	}
}
