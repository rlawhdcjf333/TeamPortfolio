#include "pch.h"
#include "GameEvent.h"
#include "Camera.h"

IDelayEvent::IDelayEvent(float delayTime)
{
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
}

void IDelayEvent::Start()
{
}

bool IDelayEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		return true;
	}

	return false;
}

///============================================================ <
/// ���ѷα� �̺�Ʈ
///============================================================ <

IPrologueEvent::IPrologueEvent()
{
	mRect = RectMake(0, 0, WINSIZEX, WINSIZEY);
	mDialogue = L"�׷� ���� �Ͼ ���̴�";
	mDialogue1 = L"���� ���� ������ �ھտ� �ΰ�...";
	mDialogue2 = L"�������� ���ļ� ��ġ���� ���� ������ �Ǵ� ����...";
	mDialogue3 = L"...���� �� �� �ִ�.";
	mEndRequest = L"����Ϸ��� ����";
	mTime = 2.f;
	mCurrentTime = 0.f;
	hdc = IMAGEMANAGER->FindImage(L"Title")->GetHDC();
}

void IPrologueEvent::Start()
{
	
}

bool IPrologueEvent::Update()
{
	HBRUSH newb = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH oldb = (HBRUSH)SelectObject(hdc, newb);
	RenderRect(hdc, mRect);
	SelectObject(hdc, oldb);
	DeleteObject(newb);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 100, 100, mDialogue.c_str(), mDialogue.size());

	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime > 0.5f) 
		TextOut(hdc, 100, 150, mDialogue1.c_str(), mDialogue1.size());
	if (mCurrentTime > 1.f) 
		TextOut(hdc, 100, 200, mDialogue2.c_str(), mDialogue2.size());
	if (mCurrentTime > 1.5f) 
		TextOut(hdc, 100, 250, mDialogue3.c_str(), mDialogue3.size());

	if(mCurrentTime > 2.f) 
		TextOut(hdc, 800, 500, mEndRequest.c_str(), mEndRequest.size());

	if (mCurrentTime > 2.f and Input::GetInstance()->GetKeyUp(VK_RETURN)) 
	{
		IMAGEMANAGER->FindImage(L"TitleClearBuffer")->Render(hdc, 0, 0);
		return true;
	}
	return false;
}

//UI�������̺�Ʈ
UIDelayEvent::UIDelayEvent(string objectname,float delayTime)
{
	targetUI = objectname;
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
}

void UIDelayEvent::Start()
{
}

bool UIDelayEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		ObjectManager::GetInstance()->FindObject(targetUI)->SetIsActive(true);
		return true;
	}
	return false;
}
