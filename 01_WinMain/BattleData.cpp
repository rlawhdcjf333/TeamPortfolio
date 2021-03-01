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
	
	mBlueTeam.mSelectChamp.clear();
	mBlueTeam.mSelectChamp.shrink_to_fit();

	mRedTeam.mSelectChamp.clear();
	mRedTeam.mSelectChamp.shrink_to_fit();

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
		else if(i >= 3 && i < 5)
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
		}
		for (int i = 0; i < 2; ++i)
		{
			if (mBlueTeam.mWaitStaff[i] == waittoselect)
				mBlueTeam.mWaitStaff[i] = selecttowait;
		}
		break;
	case Team::Red:
		for (int i = 0; i < 3; ++i)
		{
			if (mRedTeam.mSelectStaff[i] == selecttowait)
				mRedTeam.mSelectStaff[i] = waittoselect;
		}
		for (int i = 0; i < 2; ++i)
		{
			if (mRedTeam.mWaitStaff[i] == waittoselect)
				mRedTeam.mWaitStaff[i] = selecttowait;
		}
		break;
	} 
}

void BattleData::ChampBan(Champ * ban)
{
	for (int i = 0; i < 2; ++i)
	{
		if (mBanChamp[i]==nullptr)	//nullptr 이면
		{
			mBanChamp[i] = ban;
			return;
		}
	}
}

void BattleData::ChampSelect(Staff * st, Champ * c)
{
	if (GetChampTeam((GameObject*)c) == Team::None)//밴이 되거나 레드나 블루팀에서 선택한 챔피언이면
	{
		mSelectChamp.emplace_back(c);
		c->SetStaff(st);

		SOUNDPLAYER->Play(L"Pick", 0.2f);

		Team temp = GetStaffTeam(st);
		switch (temp)
		{
		case Team::Blue:
			mBlueTeam.mSelectChamp.emplace_back(c);
			break;
		case Team::Red:
			mRedTeam.mSelectChamp.emplace_back(c);
			break;
		}
	}
}

int BattleData::BanCount()
{
	if (mBanChamp[0] == nullptr) return 0;
	else if (mBanChamp[1] == nullptr) return 1;
	else if (mBanChamp[1]) return 2;
}
void BattleData::ChampSwap(Champ* cp1, Champ * cp2)
{
	//플레이어의 selectstaff인지 확인(혹시 몰라서 만듬)
	bool checkMyTeam = false;
	Staff* st1 = (Staff*)cp1->GetStaff();
	Staff* st2 = (Staff*)cp2->GetStaff();
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
	Staff* temp;
	temp = st1;
	cp1->SetStaff(st2);
	cp2->SetStaff(temp);

	int index1 = 0;
	int index2 = 0;
	switch (mPlayerTeam)
	{
	case Team::Blue:
		for (int i = 0; i < 3; ++i)
		{
			if (mBlueTeam.mSelectChamp[i] == cp1)
				index1 = i;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (mBlueTeam.mSelectChamp[i] == cp2)
				index2 = i;
		}
		mBlueTeam.mSelectChamp[index1] = cp2;
		mBlueTeam.mSelectChamp[index2] = cp1;
		break;
	case Team::Red:
		for (int i = 0; i < 3; ++i)
		{
			if (mRedTeam.mSelectChamp[i] == cp1)
				index1 = i;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (mRedTeam.mSelectChamp[i] == cp2)
				index2 = i;
		}
		mRedTeam.mSelectChamp[index1] = cp2;
		mRedTeam.mSelectChamp[index2] = cp1;
		break;
	}
}

vector<Champ*> BattleData::GetSelectChampList(Team t)
{
	TeamData team;
	switch (t)
	{
	case Team::Red:
		team = mRedTeam;
		break;
	case Team::Blue:
		team = mBlueTeam;
	}
	return team.mSelectChamp;
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

bool BattleData::IsSelectChamp(Champ* select)
{
	if(mBanChamp[0] == select)
		return true;
	if (mBanChamp[1] == select)
		return true;
	for (int i = 0; i < mSelectChamp.size(); ++i)
	{
		if (mSelectChamp[i]->GetName() == select->GetName())
			return true;
	}
	return false;
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

void BattleData::PlusWincount(Team t)
{
	if (t == Team::Red)
	{
		mRedTeam.mWinCount++;
		mRedTeam.mDirector->SetRound(mRedTeam.mDirector->GetRound() + 1);
	}
	else if (t == Team::Blue)
	{
		mBlueTeam.mWinCount++;
		mBlueTeam.mDirector->SetRound(mBlueTeam.mDirector->GetRound() + 1);

	}
	else
	{
		assert(false);
		MessageBox(_hWnd, L"승리 팀 지정 실패", L"오류", MB_OK);
	}
}

bool BattleData::IsEnd() {	//PickBattle Scene 종료여부
	if (mBlueTeam.mWinCount >= 2)
	{
		mBlueTeam.mDirector->PlusWin();
		mRedTeam.mDirector->PlusLose();

		return true;
	}
	if (mRedTeam.mWinCount >= 2)
	{
		mRedTeam.mDirector->PlusWin();
		mBlueTeam.mDirector->PlusLose();

		return true;
	}
	return false;
}
void BattleData::TeamChange()
{
	ChampManager::GetInstance()->Release();
	mBlueTeam.mSelectChamp.clear();
	mRedTeam.mSelectChamp.clear();
	mBanChamp[0] = nullptr;
	mBanChamp[1] = nullptr;
	mSelectChamp.clear();

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
	/*
	if (mBlueTeam.mSelectStaff[0] == (Staff*)champ->GetStaff())
		return Team::Blue;
	if (mBlueTeam.mSelectStaff[1] == (Staff*)champ->GetStaff())
		return Team::Blue;
	if (mBlueTeam.mSelectStaff[2] == (Staff*)champ->GetStaff())
		return Team::Blue;

	if (mRedTeam.mSelectStaff[0] == (Staff*)champ->GetStaff())
		return Team::Red;
	if (mRedTeam.mSelectStaff[1] == (Staff*)champ->GetStaff())
		return Team::Red;
	if (mRedTeam.mSelectStaff[2] == (Staff*)champ->GetStaff())
		return Team::Red;
	*/
	for (int i = 0; i < mBlueTeam.mSelectChamp.size(); ++i)
	{
		if (mBlueTeam.mSelectChamp[i] == champ)
			return Team::Blue;
	}
	for (int i = 0; i < mRedTeam.mSelectChamp.size(); ++i)
	{
		if (mRedTeam.mSelectChamp[i] == champ)
			return Team::Red;
	}
	return Team::None;
}

Team BattleData::GetStaffTeam(Staff* st)
{
	if (mBlueTeam.mSelectStaff[0] == st)
		return Team::Blue;
	if (mBlueTeam.mSelectStaff[1] == st)
		return Team::Blue;
	if (mBlueTeam.mSelectStaff[2] == st)
		return Team::Blue;

	if (mRedTeam.mSelectStaff[0] == st)
		return Team::Red;
	if (mRedTeam.mSelectStaff[1] == st)
		return Team::Red;
	if (mRedTeam.mSelectStaff[2] == st)
		return Team::Red;
	return Team::None;
}

Director* BattleData::GetDirector(Team t)
{
	TeamData team;
	switch (t)
	{
	case Team::Red:
		team = mRedTeam;
		break;
	case Team::Blue:
		team = mBlueTeam;
	}
	return team.mDirector;
}

Director* BattleData::GetMyDirector()
{
	if (mPlayerTeam == Team::Red)
	{
		return mRedTeam.mDirector;
	}
	else
	{
		return mBlueTeam.mDirector;
	}
}

bool BattleData::IsWinning (Staff* staff)
{
	Director* dir = staff->GetMyDirector();
	Director* enemy;
	if (mBlueTeam.mDirector == dir)
	{
		enemy = mRedTeam.mDirector;
	}
	else
	{
		enemy = mBlueTeam.mDirector;
	}

	if (enemy->GetRound() < dir->GetRound()) { return true; }

	return false;
}

Champ* BattleData::GetSelectChamp(Team t, int index)
{
	TeamData team;
	switch (t)
	{
	case Team::Red:
		team = mRedTeam;
		break;
	case Team::Blue:
		team = mBlueTeam;
	}
	return team.mSelectChamp[index]; 
}
