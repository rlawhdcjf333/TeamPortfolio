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
	for (int i = 1; i < 5; i++) {
		Director* director = (Director*)ObjectManager::GetInstance()->FindObject("Director" + to_string(i));
		mDirectorList.push_back(director);
	}
}

void ScheduleManager::ShuffleDirectorList()
{
	Director* director = mDirectorList[1];
	mDirectorList.erase(mDirectorList.begin() + 1);
	mDirectorList.push_back(director);
}