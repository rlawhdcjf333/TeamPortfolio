#pragma once

class Director;
class ScheduleManager {
	
	Singleton(ScheduleManager)

	vector<Director*> mDirectorList;
	map<int, vector<Director*>> mSchedule;

	int mToday;
public:

	void Init();
	void AddSchedule();
	void LoadDirectorList();
	void ShuffleDirectorList();

	map<int, vector<Director*>> GetSchedule() const { return mSchedule; }
	vector<Director*> GetDayDirector(int key) { return mSchedule.find(key)->second; }


	Director* GetPlayer(int Director1Week) { return mSchedule[Director1Week][0]; }
	Director* GetEnemy(int Director1Week) { return mSchedule[Director1Week][1]; }
	Director* GetOutFight1(int Director1Week) { return mSchedule[Director1Week][2]; }
	Director* GetOutFight2(int Director1Week) { return mSchedule[Director1Week][3]; }


};