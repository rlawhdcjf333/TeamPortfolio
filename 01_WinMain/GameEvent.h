#pragma once
#include "Camera.h"
//interface class : ���������Լ����� ������ �ִ� Ŭ����
class IEvent
{
public:
	//�ڵ������� ���� �����Լ��� �ȴ�
	virtual void Start() = 0;	//�̺�Ʈ ������ �� ȣ��Ǵ� �Լ�
	//�����ϴٰ� ������ return true
	virtual bool Update() = 0;	//�̺�Ʈ ������Ʈ �Լ�
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