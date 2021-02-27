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
};