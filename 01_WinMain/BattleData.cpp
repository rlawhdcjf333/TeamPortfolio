#include "pch.h"
#include "BattleData.h"
#include "Director.h"
#include "Staff.h"
#include "StaffSelect.h"
#include "Champ.h"

void BattleData::RoundReset()
{
	for (int i = 0; i < mSelectChamp.size(); ++i)
	{
		mSelectChamp[i]->SetStaff(nullptr);
	}
	mSelectChamp.clear();
	mSelectChamp.shrink_to_fit();
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

	for (int i = 0; i < t.mStaffList.size(); ++i)//배열이니 새로 초기화할때 안비워줘도댐
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
		if (!mBanChamp[i])	//nullptr이 아니면
		{
			mBanChamp[i] = ban;
			return;
		}
	}
}

bool BattleData::ChampSelect(Staff * st, Champ * c)
{
	if(GetChampTeam(c) != Team::None)//밴이 되거나 레드나 블루팀에서 선택한 챔피언이면
		return false;

	mSelectChamp.push_back(c);
	return true;
}

int BattleData::BanCount()
{
	if (mBanChamp[0] == nullptr) return 0;
	else if (mBanChamp[1] == nullptr) return 1;
	else if (mBanChamp[1]) return 2;
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
	Champ* champ1 = nullptr;
	Champ* champ2 = nullptr;
	for (int i = 0; i < mSelectChamp.size(); ++i)
	{
		if (mSelectChamp[i]->GetStaff() == st1)
			champ1 = mSelectChamp[i];
		if (mSelectChamp[i]->GetStaff() == st2)
			champ2 = mSelectChamp[i];
	}
	temp = champ1;
	champ1 = champ2;
	champ2 = temp;
}

void BattleData::Feedback(int i)//i = 버튼 번호(1~4)
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
		wstring alert = L"플레이어 팀이 지정되지 않았거나 잘못된 값이 설정되었습니다.";
		wstring caption = L"오류!";
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
	//바꿀거 mPlayerTeam,mBlueTeam<->mRedTeam
	if (mPlayerTeam == Team::Blue)	//mPlayerTeam : 함수 내에서 팀 식별용으로 쓰이는 변수 반전
		mPlayerTeam = Team::Red;
	else if (mPlayerTeam == Team::Red)	//else if <- 둘 중 하나만 실행되야해서
		mPlayerTeam = Team::Blue;

	TeamData temp = mBlueTeam;	//temp에 블루팀 데이터 복사
	mBlueTeam = mRedTeam;	//레드팀 데이터를 블루팀으로 복사
	mRedTeam = temp;		//temp(블루팀 복사본)을 레드팀으로 복사 하면 스왑이 됐겠지?
}

Director * BattleData::GetEnemyDirector()
{
	if (mPlayerTeam == Team::Blue)
		return mRedTeam.mDirector;
	if (mPlayerTeam == Team::Red)
		return mBlueTeam.mDirector;
}

Team BattleData::GetChampTeam(GameObject * pt)
{
	Champ* champ = (Champ*)pt;
	
	if (mBanChamp[0] == champ)
		return Team::Ban;
	if (mBanChamp[1] == champ)
		return Team::Ban;

	if (mBlueTeam.mSelectStaff[0] == champ->GetStaff())
		return Team::Blue;
	if (mBlueTeam.mSelectStaff[1] == champ->GetStaff())
		return Team::Blue;
	if (mBlueTeam.mSelectStaff[2] == champ->GetStaff())
		return Team::Blue;

	if (mRedTeam.mSelectStaff[0] == champ->GetStaff())
		return Team::Red;
	if (mRedTeam.mSelectStaff[1] == champ->GetStaff())
		return Team::Red;
	if (mRedTeam.mSelectStaff[2] == champ->GetStaff())
		return Team::Red;

	return Team::None;
}
