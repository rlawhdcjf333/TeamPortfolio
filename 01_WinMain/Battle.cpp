#include "pch.h"
#include "Battle.h"

Battle::Battle() : UI("Battle")
{
	mIsActive = false;
}

void Battle::Init()
{
	//IMAGEMANAGER->LoadFromFile(L"BattleGround", Resources(L"battle.bmp"), 1280, 720, true);	//�������� â ���°�
	IMAGEMANAGER->LoadFromFile(L"BattleGround", Resources(L"battle2.bmp"), 1280, 720, true);	//�������� â �ִ°�, �������� ���� ���� �Ѵ� ����
	mImage = IMAGEMANAGER->FindImage(L"BattleGround");

	mTime = 60;
	mDeltaTime = 0;
}

void Battle::Release()
{
}

void Battle::Update()
{
	if (!mIsActive)
		return;

	if (mTime == 0)
	{
		mTime = 60;
		mIsActive = false;
		//���Ḧ ǥ���� UI�� ���� ������ �� UI������ Battle�� peedback active�� ����
		//ObjectManager::GetInstance()->FindObject("Peedback");		//Peedback �����Ǹ� �ּ� ����
	}
	mDeltaTime += Time::GetInstance()->DeltaTime();	//�ϴ��غ�, �� �����ҷ���.. DeltaTime�� 0.n�� �Ǽ��ΰ�?
	if (mDeltaTime >= 1)
	{
		mDeltaTime = 0.f;
		mTime -= 1;//��ŸŸ�� = 1�������� ���� �ð�, 1�ʸ� ���Ϸ���? 
	}
}

void Battle::Render(HDC hdc)
{
	//1. ���
	mImage->Render(hdc, 0, 0);
	//2. UI : ��ܺκ� + �¿� ���� + ų���� �α� �� �������ð�
	TextOut(hdc, 640, 60, to_wstring(mTime).c_str(), to_wstring(mTime).size());
	//3. è��
}
