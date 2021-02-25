#include "pch.h"
#include "Battle.h"

Battle::Battle() : UI("Battle")
{
	mIsActive = false;
}

void Battle::Init()
{
	//���������ʷ� ���� �̹����� �����α���
	IMAGEMANAGER->LoadFromFile(L"BattleUI", Resources(L"battleUI.bmp"), 1280, 720, true);
	mUI = IMAGEMANAGER->FindImage(L"BattleUI");
	IMAGEMANAGER->LoadFromFile(L"BattleGround", Resources(L"battleback.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BattleGround");

	mTime = 60;
	mDeltaTime = 0.f;
}

void Battle::Release()
{
}

void Battle::Update()
{
	if (!mIsActive)
		return;

	if (mTime == 0 || Input::GetInstance()->GetKeyDown('G'))
	{
		mTime = 60;
		mIsActive = false;
		//���Ḧ ǥ���� UI�� ���� ������ �� UI������ Battle�� peedback active�� ����
		ObjectManager::GetInstance()->FindObject("Peedback")->SetIsActive(true);		//Peedback �����Ǹ� �ּ� ����
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
	mUI->Render(hdc, 0, 0);
	TextOut(hdc, 640, 60, to_wstring(mTime).c_str(), to_wstring(mTime).size());
	//3. è��
}
