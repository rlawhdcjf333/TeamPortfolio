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

class EndEvent : public IEvent
{
	class GameObject* mNpc;
	class GameObject* mPlayer;
	float CameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float CameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;

public:
	void Start()override;
	bool Update()override;
	EndEvent(class GameObject* target1, class GameObject* target2);
};

class IChangeCameraTargetEvent : public IEvent
{
	class GameObject* mTarget;
public:
	IChangeCameraTargetEvent(class GameObject* target);

	void Start()override;
	bool Update()override;
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