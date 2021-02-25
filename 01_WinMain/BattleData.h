#pragma once
class GameObject;
class Director;
class Staff;
class Champ;

enum class Team {	//�ĺ������� ������ ������µ� �Ⱦ��� �ٸ�������� ����, �׷��� �ϴ� ����
	Blue = 0,
	Red = 1
};

struct TeamData
{
	Director* mDirector;		//����
	vector<Staff*> mStaffList;	//������ ��� ����, ��� �ǳ�?
	Staff* mSelectStaff[3];		//��������
	Staff* mWaitStaff[2];		//��⼱��
	
	int mKillCount;				//�� ������ ų ��
	int mWinCount;				//�� �¸���
};

class BattleData	//�̱������� ����� ����
{
	Singleton(BattleData);
protected:
	Team PlayerTeam;

	//���2 mTeamData ����ü ���;
	TeamData mBlueTeam;
	TeamData mRedTeam;

	map<Staff*, Champ*> mSelectedChamp;	//������(key,first)�� ���� è�Ǿ�(value,second), key�� TeamData.mSelectStaff

	Staff* mStaff;	//���� �ʿ� Ű������ �����༮�� ���� ����, �Լ������� ���ϰŰ��� ����
	Champ* mChamp;	//��� ����, ���� map�� value�� ��Ƽ� 

	Champ* mBanChamp[2];	//��� è�Ǿ�, GameObject*�� �ؾ��ϳ�?
	
	/*//���1 ���� ���� �����
	Director* mTeam[2];		//
	
	map<Team, vector<Staff*>> mStaffList;	//���� ���� ������
	map<Team, Staff*[3]> mSelectStaff;	//��������
	map<Team, Staff*[2]> mWaitStaff;	//��⼱��

	map<Team, int>	mKillCount;
	map<Team, int> mWinCount;
	*/
public:

};
/*
	1.Director �� (Red, Blue)
	2.�÷��̾��� �� -> StaffSelect�� BanPick~ChampCheck���� �˾ƾ���
	3.��� è��
	4.�������� ������ è�� -> 5.ChampCheck���� ���� ������ ��ȯ�ϴ� �Լ�
	6.����� Red�� Blue�� ų ��
	7.Red,Blue�� ���� �¸� �� -> BattleUI�� �¼���ŭ �̹��� ǥ��

	<�Լ�>
	1. �÷��̾� �� ����
	2. �÷��̾ ������ ���� ���� mBlueTeam�� mRedTeam �ʱ�ȭ(���� �Է�), ������� �÷��̾��� ��� ����� ���� : PickBattle �� ���۽� ȣ��
		mSelectStaff�� mWaitStaff�� mStaffList�� ��� ������� �ִ´� 
	3. mSelectStaff�� mWaitStaff�� ����?�ϴ� �Լ� : StaffSelect UI���� ��⼱�� ����(Staff* ����1) �� ��ü�� ���������� ����(Staff* ����2)�� ȣ��,
												   2���� Staff* ���ڸ� �޾� ������ ��ġ�� �ٲ���
	4. ���õ� Champ*�� mBanChamp �迭�� �־��ִ� �Լ� : BanPick UI���� ȣ��
	5. è���� ������ ������ �� Staff*�� �ް�, Champ�� ������ Champ*�� �޾� mSelectedChamp map�� insert : BanPick UI���� ȣ��
	6. ChampCheck���� ���� ������ ��ȯ�ϴ� �Լ� : ChampCheck UI���� ȣ��
	7. ��Ʋ ������ �Լ�.........ų�� �߻��ϸ� mKillCount++ : Battle UI���� ȣ��
	8. mKillCount�� Ȯ���ϰ� mWinCount++, mKillCount = 0�ϴ� �Լ� : BattleUI(Battle�̶� �ٸ�����) UI���� BattleResult UI active=true ���� ȣ��
	9. ���� ���ο� ���� �ǵ���� �ϰ� Staff���� ������� �����Ű�� �Լ� : Peedback UI���� ȣ��
*/