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
	Director* mDirector;		//����
	vector<Staff*> mStaffList;	//������ ��� ����
	Staff* mSelectStaff[3] = { nullptr ,nullptr,nullptr };		//��������
	Staff* mWaitStaff[2] = { nullptr ,nullptr };		//��⼱��

	int mKillCount = 0;				//�� ������ ų ��
	int mWinCount = 0;				//�� �¸���
};


class BattleData	//�̱������� ����� ����
{
	Singleton(BattleData);
private:


	Team mPlayerTeam;//������ -> switch�� //

	//mTeamData ����ü ���; //�����̽� cto �̱��� ���°� ��
	TeamData mBlueTeam;
	TeamData mRedTeam;

	Champ* mBanChamp[2];	//��� è�Ǿ�, GameObject*�� �ؾ��ϳ�? //������� Gameobject �� �� ���ϱ���   mIsActive ����Ű�� �Ÿ�
	vector<Champ*> mSelectChamp;	//������(key,first)�� ���� è�Ǿ�(value,second), key�� TeamData.mSelectStaff

	Staff* mStaff;	//���� �ʿ� Ű������ �����༮�� ���� ����, �Լ������� ���ϰŰ��� ���� //currentStaff��� �ϸ� �ǰڳ�
	Champ* mChamp;	//��� ����, ���� map�� value�� ��Ƽ� //�̰� currentPick

public:
	void RoundReset();	//��� �� ���� �ʱ�ȭ

	void SetPlayerTeam(Team t) { mPlayerTeam = t; }
	Team GetPlayerTeam() { return mPlayerTeam; }

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
	bool IsEnd() {	//PickBattle Scene ���Ῡ��
		if (mBlueTeam.mWinCount >= 2)
			return true;
		if (mRedTeam.mWinCount >= 2)
			return true;
		return false;
	}


	void SetTeam(Team t, Director * dir);	//Team�ʱ�ȭ, �̰� �ؾ� GetEnemyDirector��������
	TeamData LoadStaffList(Director* dir);	//SetTeam���� ȣ���� StaffList�ʱ�ȭ�� �Լ�
	void StaffSwap(Staff* waittoselect,Staff* selecttowait);//1:��⼱��,2:��ü�� ��������

	//void Pick(Champ* c, Staff* s) { GameObject* staff = (GameObject*)s; c->SetStaff(staff); }
	void ChampBan(Champ* ban);
	int BanCount();
	GameObject* GetBanOb(int index) { return (GameObject*)mBanChamp[index]; }
	Champ* GetBanCp(int index) { return mBanChamp[index]; }

	bool ChampSelect(Staff* st, Champ* c);//�� �Լ��� ȣ���ϰ� true�� ������ ���� ������ �� �ϵ�����
	void ChampSwap(Staff* st1, Staff* st2);

	void Feedback(int i);
	void UpdateCondition(TeamData t, int con);

	void SetResult();

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

	vector<Staff*> GetEnemyStaff();

	void TeamChange();//���� ���� �� ����� ����� ��ü
	Director* GetEnemyDirector();
	
	Team GetChampTeam(GameObject* pt);
};
#define BData BattleData::GetInstance()
/*
	<�Լ�>
	1. �÷��̾� �� ���� -> SetPlayerTeam
	2. mBlueTeam�� mRedTeam �ʱ�ȭ(���� �Է�), : PickBattle �� ���۽� ȣ�� -> SetTeam
	   mSelectStaff�� mWaitStaff�� mStaffList�� ��� ������� �ִ´� -> LoadStaffList
	3. mSelectStaff�� mWaitStaff�� ����?�ϴ� �Լ� : StaffSelect UI���� ��⼱�� ����(Staff* ����1) �� ��ü�� ���������� ����(Staff* ����2)�� ȣ��,
												   2���� Staff* ���ڸ� �޾� ������ ��ġ�� �ٲ��� -> StaffSwap
	4. ���õ� Champ*�� mBanChamp �迭�� �־��ִ� �Լ� : BanPick UI���� ȣ��		-> ChampBan
	5. è���� ������ ������ �� Staff*�� �ް�, Champ�� ������ Champ*�� �޾� mSelectedChamp map�� insert : BanPick UI���� ȣ�� -> ChampSelect
	6. ChampCheck���� ���� ������ ��ȯ�ϴ� �Լ� : ChampCheck UI���� ȣ��	-> ChampSwap
	7. ��Ʋ ������ �Լ�.........ų�� �߻��ϸ� mKillCount++ : Battle UI���� ȣ��
	8. mKillCount�� Ȯ���ϰ� mWinCount++, mKillCount = 0�ϴ� �Լ� : BattleUI(Battle�̶� �ٸ�����) UI���� BattleResult UI active=true ���� ȣ��
	->UpdateWinCount
	9. ���� ���ο� ���� �ǵ���� �ϰ� Staff���� ������� �����Ű�� �Լ� : Feedback UI���� ȣ�� -> Feedback

	+
	10. Director* �� ��/�� ���� -> HomeScene���� ���ư����� BattleResult UI���� ȣ��
*/