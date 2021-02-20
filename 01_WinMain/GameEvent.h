#pragma once
#include "Camera.h"
//interface class : 순수가상함수만을 가지고 있는 클래스
class IEvent
{
public:
	//자동적으로 순수 가상함수가 된다
	virtual void Start() = 0;	//이벤트 시작할 때 호출되는 함수
	//실행하다가 끝나면 return true
	virtual bool Update() = 0;	//이벤트 업데이트 함수
};

class IDelayEvent : public IEvent
{
	float mCurrentTime;
	float mDelayTime;
public:
	IDelayEvent(float delayTime);

	void Start()override;
	bool Update()override;
};

class IPrologueEvent : public IEvent {

	float mCurrentTime;
	float mTime;
	RECT mRect;
	wstring mDialogue;
	wstring mDialogue1;
	wstring mDialogue2;
	wstring mDialogue3;
	wstring mEndRequest;
	HDC hdc;

public:
	IPrologueEvent();
	void Start()override;
	bool Update()override;

};