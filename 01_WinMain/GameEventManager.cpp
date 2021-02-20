#include "pch.h"
#include "GameEventManager.h"

#include "GameEvent.h"

GameEventManager::GameEventManager()
{
}

GameEventManager::~GameEventManager()
{
	RemoveAllEvent();
}

void GameEventManager::RemoveAllEvent()
{
	while(!mEventQueue.empty()){

		SafeDelete(mEventQueue.front());
		mEventQueue.pop();
	}
}

void GameEventManager::Update()
{
	if (mEventQueue.empty())
		return;

	bool isEnd = mEventQueue.front()->Update();
	if (isEnd == true)
	{
		SafeDelete(mEventQueue.front());
		mEventQueue.pop();

		if (mEventQueue.size() != 0)
		{
			mEventQueue.front()->Start();
		}
	}
}

void GameEventManager::PushEvent(IEvent * event)
{
	if (mEventQueue.size() == 0)
	{
		event->Start();
	}
	mEventQueue.push(event);
}

bool GameEventManager::IsPlaying()
{
	if (mEventQueue.empty())return false;
	return true;
}
