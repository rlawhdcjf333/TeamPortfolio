#include "pch.h"
#include "BanPick.h"
#include "Child.h"
BanPick::BanPick() : UI("BanPick")
{
	mIsActive = false;
	mNowState = "BlueBan";
}

void BanPick::Init()
{
	LoadFromFile("pick_battle_level2");
	IMAGEMANAGER->LoadFromFile(L"BanPick", Resources(L"BanPick.bmp"), 1280, 720, true);
	mImage = IMAGEMANAGER->FindImage(L"BanPick");
}

void BanPick::Release()
{
}

void BanPick::Update()
{
	if (!mIsActive)
		return;
	//��� ���� - ���� �Ĺ� - ��� 1�� - ���� 1,2�� - ��� 2,3�� - ���� 3��
	//1. BlueBan : ChampListUI �����ְ�.. �ű洩���� �� è�� ��ǰ� ��, ���� Blue ���� ��ǻ�͸� ������
	//2. RedBan : ���� ��������, �� �� è���� ���� �Ұ�
	//3. BluePick1 : �÷��� �� è�� 1�� ����	->	Ŭ���� �Ͼ��... è�� ������ ������ ���� ����?
	//4. RedPick2 : �÷��� �� è�� 2�� ����
	//5. BluePick2 : �÷��� �� è�� 2�� ����
	//6. RedPick2 : �÷��� �� è�� 1�� ����
	//7. �� ������ ������ ChampCheckUIȰ�� + �÷��̾��� �� ���������� è�Ǿ��� �ٲ� �� �ִ� �ð��� �־�����,
	if (Input::GetInstance()->GetKeyDown(MK_LBUTTON))//�׽�Ʈ���� è������Ʈ �ϼ��Ǹ� ����
	{
		BanPickGuide* tptr = (BanPickGuide*)ObjectManager::GetInstance()->FindObject("BanPickGuide");
		tptr->NextFrame();//BanPickGuideŬ���� ���� �Լ�...�� �����Ϸ��� �迡�� �ٿ�ĳ����
	}
}

void BanPick::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->Render(hdc, 0, 0);
	}
}
