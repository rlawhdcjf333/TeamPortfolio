#pragma once
class Director;
class ScheduleManager {
	
	Singleton(ScheduleManager)

private:

	vector<string> mDirectorList;
	map<int, vector<string>> mSchedule;
	int mToday;


public:

	void Init();
	void AddSchedule();
	void ShuffleDirectorList();

	map<int, vector<Director*>> GetSchedule() 
	{
		map <int, vector<Director*>> result;

		for (int i = 1; i <= mSchedule.rbegin()->first; i++)
		{
			auto temp = GetDayDirector(i);
			for (Director* elem : temp)
			{
				result[i].push_back(elem);
			}
		}

		return result;

	}
	vector<Director*> GetDayDirector(int key)
	{
		vector <Director*> result;

		auto temp = mSchedule[key];

		Director* one = (Director*)ObjectManager::GetInstance()->FindObject(temp[0]);
		Director* two = (Director*)ObjectManager::GetInstance()->FindObject(temp[1]);
		Director* three = (Director*)ObjectManager::GetInstance()->FindObject(temp[2]);
		Director* four = (Director*)ObjectManager::GetInstance()->FindObject(temp[3]);

		result.push_back(one);
		result.push_back(two);
		result.push_back(three);
		result.push_back(four);
		
		return result;
	}


	Director* GetPlayer(int Director1Week) 
	{
		return (Director*)ObjectManager::GetInstance()->FindObject(mSchedule[Director1Week][0]); 
	}
	Director* GetEnemy(int Director1Week) 
	{ 
		return (Director*)ObjectManager::GetInstance()->FindObject(mSchedule[Director1Week][1]);
	}
	Director* GetOutFight1(int Director1Week) 
	{
		return (Director*)ObjectManager::GetInstance()->FindObject(mSchedule[Director1Week][2]);
	}
	Director* GetOutFight2(int Director1Week) 
	{
		return (Director*)ObjectManager::GetInstance()->FindObject(mSchedule[Director1Week][3]);
	}


};