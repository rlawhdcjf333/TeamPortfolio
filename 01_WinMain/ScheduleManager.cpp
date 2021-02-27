#include "pch.h"
#include "ScheduleManager.h"
#include "Director.h"

void ScheduleManager::Init()
{
	LoadDirectorList();
	
	for (int i = 1; i < mDirectorList.size(); i++) {
		mSchedule.insert(make_pair(i, mDirectorList));
		ShuffleDirectorList();
	}
}

void ScheduleManager::AddSchedule()
{

}

void ScheduleManager::LoadDirectorList()
{
	vector <Director*> tmp;

	for (int i = 1; i < 5; i++) {
		Director* director = (Director*)ObjectManager::GetInstance()->FindObject("Director" + to_string(i));
		tmp.push_back(director);
	}

	mDirectorList.assign(tmp.begin(), tmp.end());
}

void ScheduleManager::ShuffleDirectorList()
{
	Director* director = mDirectorList[1];
	mDirectorList.erase(mDirectorList.begin() + 1);
	mDirectorList.push_back(director);
}