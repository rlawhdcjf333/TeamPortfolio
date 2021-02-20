#pragma once
class GameEventManager
{
	Singleton(GameEventManager)
private:
	//�� queue��� �ڷᱸ�� �����ؼ� queue�� �ٲ����
	queue <class IEvent*> mEventQueue;
public:
	GameEventManager();
	~GameEventManager();

	void RemoveAllEvent();
	void Update();

	void PushEvent(class IEvent* event);
	bool IsPlaying();
};

