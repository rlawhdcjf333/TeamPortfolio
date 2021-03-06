#pragma once
class GameObject;
class Director;
class Staff;
class Champ;

enum class Team {
	None,
	Ban,
	Blue,
	Red
};

struct TeamData
{
	Director* mDirector;		//감독
	vector<Staff*> mStaffList;	//감독의 모든 선수
	Staff* mSelectStaff[3] = { nullptr ,nullptr,nullptr };		//출전선수
	Staff* mWaitStaff[2] = { nullptr ,nullptr };		//대기선수

	int mKillCount = 0;				//한 라운드의 킬 수
	int mWinCount = 0;				//판 승리수

	vector<Champ*>mSelectChamp;
};


class BattleData	//싱글턴으로 만들어 저장
{
	Singleton(BattleData);
private:


	Team mPlayerTeam;//팀색깔 -> switch용

	//mTeamData 구조체 사용; 
	TeamData mBlueTeam;
	TeamData mRedTeam;

	Champ* mBanChamp[2];	//밴된 챔피언
	vector<Champ*> mSelectChamp;


public:
	void RoundReset();	//밴과 픽 정보 초기화

	void SetPlayerTeam(Team t) { mPlayerTeam = t; }
	Team GetPlayerTeam() { return mPlayerTeam; }
	Team GetEnemyTeam()
	{
		if (mPlayerTeam == Team::Red) return Team::Blue;
		else return Team::Red;
	}

	int GetKillCount(Team t) { 
		if(t == Team::Blue)
			return mBlueTeam.mKillCount;
		if (t == Team::Red)
			return mRedTeam.mKillCount;
	}
	int GetWinCount(Team t) {
		if (t == Team::Blue)
			return mBlueTeam.mWinCount;
		if (t == Team::Red)
			return mRedTeam.mWinCount;
	}
	void UpdateWinCount() {
		if (mBlueTeam.mKillCount > mRedTeam.mKillCount)
			mBlueTeam.mWinCount++;
		if (mBlueTeam.mKillCount < mRedTeam.mKillCount)
			mRedTeam.mWinCount++;
	}
	bool IsEnd();

	void SetTeam(Team t, Director * dir);	//Team초기화, 이거 해야 GetEnemyDirector쓸수있음
	TeamData LoadStaffList(Director* dir);	//SetTeam에서 호출할 StaffList초기화용 함수
	void StaffSwap(Staff* waittoselect,Staff* selecttowait);//1:대기선수,2:교체될 출전선수

	//void Pick(Champ* c, Staff* s) { GameObject* staff = (GameObject*)s; c->SetStaff(staff); }
	void ChampBan(Champ* ban);
	int BanCount();
	GameObject* GetBanOb(int index) { return (GameObject*)mBanChamp[index]; }
	Champ* GetBanCp(int index) { return mBanChamp[index]; }

	void ChampSelect(Staff* st, Champ* c);
	void ChampSwap(Champ* cp1, Champ* cp2);
	int GetSelectSize() { return mSelectChamp.size(); }
	vector<Champ*> GetSelectChampList(Team t);
	Champ* GetSelectChamp(Team t, int index);
	bool IsSelectChamp(Champ* select);

	void Feedback(int i);
	void UpdateCondition(TeamData t, int con);
	void RandomCondition();

	void SetResult();
	void PlusWincount(Team t);

	Staff* GetSelectStaff(int index) {
		if (mPlayerTeam == Team::Blue)
			return mBlueTeam.mSelectStaff[index];
		if (mPlayerTeam == Team::Red)
			return mRedTeam.mSelectStaff[index];
	}
	Staff* GetWaitStaff(int index) {
		if (mPlayerTeam == Team::Blue)
			return mBlueTeam.mWaitStaff[index];
		if (mPlayerTeam == Team::Red)
			return mRedTeam.mWaitStaff[index];
	}
	Staff* GetEnemyStaff(int index) {
		if (mPlayerTeam == Team::Blue)
			return mRedTeam.mSelectStaff[index];
		if (mPlayerTeam == Team::Red)
			return mBlueTeam.mSelectStaff[index];
	}
	vector<Staff*> GetEnemyStaff();

	void TeamChange();//라운드 종료 후 레드와 블루팀 교체
	Director* GetEnemyDirector();
	Director* GetMyDirector();
	Director* GetDirector(Team t);

	Team GetChampTeam(GameObject* pt);
	Team GetStaffTeam(Staff* st);

	bool IsWinning(Staff* staff);

};
#define BData BattleData::GetInstance()


/*
	<함수>
	1. 플레이어 팀 지정 -> SetPlayerTeam
	2. mBlueTeam과 mRedTeam 초기화(정보 입력), : PickBattle 씬 시작시 호출 -> SetTeam
	   mSelectStaff와 mWaitStaff는 mStaffList에 담긴 순서대로 넣는다 -> LoadStaffList
	3. mSelectStaff와 mWaitStaff를 스왑?하는 함수 : StaffSelect UI에서 대기선수 선택(Staff* 인자1) 후 교체할 출전선수를 선택(Staff* 인자2)시 호출,
												   2개의 Staff* 인자를 받아 서로의 위치를 바꿔줌 -> StaffSwap
	4. 선택된 Champ*를 mBanChamp 배열에 넣어주는 함수 : BanPick UI에서 호출		-> ChampBan
	5. 챔프를 선택할 순서가 된 Staff*를 받고, Champ를 선택해 Champ*를 받아 mSelectedChamp map에 insert : BanPick UI에서 호출 -> ChampSelect
	6. ChampCheck에서 같은 팀끼리 교환하는 함수 : ChampCheck UI에서 호출	-> ChampSwap
	7. 배틀 돌리는 함수.........킬이 발생하면 mKillCount++ : Battle UI에서 호출
	8. mKillCount를 확인하고 mWinCount++, mKillCount = 0하는 함수 : BattleUI(Battle이랑 다른거임) UI에서 BattleResult UI active=true 전에 호출
	->UpdateWinCount
	9. 승패 여부에 따라 피드백을 하고 Staff들의 컨디션을 변경시키는 함수 : Feedback UI에서 호출 -> Feedback

	+
	10. Director* 에 승/패 지정 -> HomeScene으로 돌아가기전 BattleResult UI에서 호출
*/