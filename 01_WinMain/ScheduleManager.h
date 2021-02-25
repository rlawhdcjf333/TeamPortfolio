#pragma once

class Director;
class ScheduleManager {
	
	Singleton(ScheduleManager)

	vector<Director*> mDirectorList;
	map<int, vector<Director*>> mSchedule;
public:

	void Init();
	void AddSchedule();
	void LoadDirectorList();
	void ShuffleDirectorList();

	map<int, vector<Director*>> GetSchedule() const { return mSchedule; }
};