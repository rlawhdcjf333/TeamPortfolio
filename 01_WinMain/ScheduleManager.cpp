#include "pch.h"
#include "ScheduleManager.h"
#include "Director.h"

void ScheduleManager::Init()
{
	mDirectorList.push_back("Director1");
	mDirectorList.push_back("Director2");
	mDirectorList.push_back("Director3");
	mDirectorList.push_back("Director4");

	for (int i = 1; i < mDirectorList.size(); i++) {
		mSchedule.insert(make_pair(i, mDirectorList));
		ShuffleDirectorList();
	}
}

void ScheduleManager::AddSchedule()
{
	auto list = ObjectManager::GetInstance()->GetPlayOff();
	mSchedule.insert(make_pair(4, list));
}


void ScheduleManager::ShuffleDirectorList()
{
	string director = mDirectorList[1];
	mDirectorList.erase(mDirectorList.begin() + 1);
	mDirectorList.push_back(director);
}