#pragma once
class GameObject;
class Director;
class Staff;
class Champ;

enum class Team {	//식별용으로 쓰려고 만들었는데 안쓰는 다른방식으로 구현, 그래도 일단 냅둠
	Blue = 0,
	Red = 1
};

struct TeamData
{
	Director* mDirector;		//감독
	vector<Staff*> mStaffList;	//감독의 모든 선수, 없어도 되나?
	Staff* mSelectStaff[3];		//출전선수
	Staff* mWaitStaff[2];		//대기선수
	
	int mKillCount;				//한 라운드의 킬 수
	int mWinCount;				//판 승리수
};

class BattleData	//싱글턴으로 만들어 저장
{
	Singleton(BattleData);
protected:
	Team PlayerTeam;

	//방법2 mTeamData 구조체 사용;
	TeamData mBlueTeam;
	TeamData mRedTeam;

	map<Staff*, Champ*> mSelectedChamp;	//스태프(key,first)별 픽한 챔피언(value,second), key는 TeamData.mSelectStaff

	Staff* mStaff;	//위에 맵에 키값으로 넣을녀석을 담을 변수, 함수용으로 쓰일거같아 만듬
	Champ* mChamp;	//↑랑 동일, 여긴 map의 value를 담아서 

	Champ* mBanChamp[2];	//밴된 챔피언, GameObject*로 해야하나?
	
	/*//방법1 각각 맵을 만들기
	Director* mTeam[2];		//
	
	map<Team, vector<Staff*>> mStaffList;	//팀에 속한 스태프
	map<Team, Staff*[3]> mSelectStaff;	//출전선수
	map<Team, Staff*[2]> mWaitStaff;	//대기선수

	map<Team, int>	mKillCount;
	map<Team, int> mWinCount;
	*/
public:

};
/*
	1.Director 팀 (Red, Blue)
	2.플레이어의 팀 -> StaffSelect와 BanPick~ChampCheck에서 알아야함
	3.밴된 챔프
	4.스태프가 선택한 챔프 -> 5.ChampCheck에서 같은 팀끼리 교환하는 함수
	6.라운드당 Red와 Blue의 킬 수
	7.Red,Blue의 라운드 승리 수 -> BattleUI에 승수만큼 이미지 표시

	<함수>
	1. 플레이어 팀 지정
	2. 플레이어가 지정된 팀에 따라 mBlueTeam과 mRedTeam 초기화(정보 입력), 상대팀은 플레이어의 상대 색깔로 지정 : PickBattle 씬 시작시 호출
		mSelectStaff와 mWaitStaff는 mStaffList에 담긴 순서대로 넣는다 
	3. mSelectStaff와 mWaitStaff를 스왑?하는 함수 : StaffSelect UI에서 대기선수 선택(Staff* 인자1) 후 교체할 출전선수를 선택(Staff* 인자2)시 호출,
												   2개의 Staff* 인자를 받아 서로의 위치를 바꿔줌
	4. 선택된 Champ*를 mBanChamp 배열에 넣어주는 함수 : BanPick UI에서 호출
	5. 챔프를 선택할 순서가 된 Staff*를 받고, Champ를 선택해 Champ*를 받아 mSelectedChamp map에 insert : BanPick UI에서 호출
	6. ChampCheck에서 같은 팀끼리 교환하는 함수 : ChampCheck UI에서 호출
	7. 배틀 돌리는 함수.........킬이 발생하면 mKillCount++ : Battle UI에서 호출
	8. mKillCount를 확인하고 mWinCount++, mKillCount = 0하는 함수 : BattleUI(Battle이랑 다른거임) UI에서 BattleResult UI active=true 전에 호출
	9. 승패 여부에 따라 피드백을 하고 Staff들의 컨디션을 변경시키는 함수 : Peedback UI에서 호출
*/