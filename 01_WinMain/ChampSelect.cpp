#include "pch.h"
#include "ChampSelect.h"
#include "Child.h"
#include "Champ.h"
ChampSelect::ChampSelect()
	:UI("ChampSelect")
{
	mIsActive = false;
}

void ChampSelect::Init()
{
	LoadFromFile("ChampFrame");//0~9 : è��, 10~11 : ��� è��
	IMAGEMANAGER->LoadFromFile(L"BackFrame", Resources(L"ChampBack.bmp"), 308, 105, 4, 1, true);
	mBackFrame = IMAGEMANAGER->FindImage(L"BackFrame");
	mState = SelectState::BlueBan;

	mChampList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Champ);
	mCurrentChamp = nullptr;

}

void ChampSelect::Release()
{
}

void ChampSelect::Update()
{
//��� ���� - ���� �Ĺ� - ��� 1�� - ���� 1,2�� - ��� 2,3�� - ���� 3��
	switch (mState)
	{
	case SelectState::BlueBan:
		//1. BlueBan : ChampListUI �����ְ�.. �ű洩���� �� è�� ��ǰ� ��, ���� Blue ���� ��ǻ�͸� ������
		//BData->ChampBan((Champ*)ChampToggle());
		//if (BData->BanCount() == 1)
		//	NextState();
		break;
	case SelectState::RedBan:
		//2. RedBan : ���� ��������, �� �� è���� ���� �Ұ�
		//GameObject* temp;
		//temp = ChampToggle();
		//if (BData->GetBan(0) != temp)
		//	BData->ChampBan((Champ*)temp);
		//if (BData->BanCount() == 2)
		//	NextState();
		break;
	//3. BluePick1 : �÷��� �� è�� 1�� ����	->	Ŭ���� �Ͼ��... è�� ������ ������ ���� ����?
	//4. RedPick2 : �÷��� �� è�� 2�� ����
	//5. BluePick2 : �÷��� �� è�� 2�� ����
	//6. RedPick2 : �÷��� �� è�� 1�� ����
	//7. �� ������ ������ ChampCheckUIȰ�� + �÷��̾��� �� ���������� è�Ǿ��� �ٲ� �� �ִ� �ð��� �־�����,
	}
}

void ChampSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		//4��° ������ x Frame�� Champ�� ���������� �ҷ����� SetIndexX(è���� ������)�� �־ �ε��� ����
		//���� -> mBackFrame->FrameRender(hdc,mButtonList[0].left, mButtonList[0].top, SetIndexX(mChampList[0]),0);
		mBackFrame->FrameRender(hdc, mButtonList[0].left, mButtonList[0].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[1].left, mButtonList[1].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[2].left, mButtonList[2].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[3].left, mButtonList[3].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[4].left, mButtonList[4].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[5].left, mButtonList[5].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[6].left, mButtonList[6].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[7].left, mButtonList[7].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[8].left, mButtonList[8].top, 0, 0);
		mBackFrame->FrameRender(hdc, mButtonList[9].left, mButtonList[9].top, 0, 0);

		mBackFrame->FrameRender(hdc, 600, 300, 1, 0);//�� �������� �����̴ϱ� 1
		mBackFrame->FrameRender(hdc, 600, 980, 1, 0);

		//è�� ���
		for (int i = 0; i < mChampList.size(); i++)
		{
			ChampRender(hdc, 232 + i * 80, 182, mChampList, i);
		}

		MouseOver(hdc);
	}
}

GameObject* ChampSelect::ChampToggle()
{
	//è���� 10���ΰɷ� �˰� ������
	mToggleButton(0, "None", [this]() {});
	mToggleButton(1, "None", [this]() {});
	mToggleButton(2, "None", [this]() {});
	mToggleButton(3, "None", [this]() {});
	mToggleButton(4, "None", [this]() {});
	mToggleButton(5, "None", [this]() {});
	mToggleButton(6, "None", [this]() {});
	mToggleButton(7, "None", [this]() {});
	mToggleButton(8, "None", [this]() {});
	mToggleButton(9, "None", [this]() {});
	return nullptr;
}

int ChampSelect::SetIndexX(GameObject* pt)
{
	int index = (int)BData->GetChampTeam(pt);
	return index;
	// Team::None(�� ����) = 0, Team::Ban(���) = 1, Team::Bleu = 2, Team::Red = 3
}

void ChampSelect::NextState()
{
	mState = (SelectState)(1 + (int)mState);
	if (mState != SelectState::RedPick1 && mState != SelectState::BluePick2)//���ǿ� ���� �ܰ���� Guide UI�� ��������ʾƾߵ�
	{
		BanPickGuide* tptr = (BanPickGuide*)ObjectManager::GetInstance()->FindObject("BanPickGuide");
		tptr->NextFrame();//BanPickGuideŬ���� ���� �Լ�...�� �����Ϸ��� �迡�� �ٿ�ĳ����
	}
}

void ChampSelect::ChampRender(HDC hdc, int x , int y, vector<GameObject*> list, int i)
{
	Champ* champ = (Champ*)list[i];
	champ->UIRender(hdc, x+2, y+2, 70, 70);

	wstring champName = champ->GetChampName();
	RECT nameBox = RectMake(x, y + 74, 77, 30);
	CallFont(hdc, 12, [hdc, champName, &nameBox]() {DrawText(hdc, champName.c_str(), champName.size(), &nameBox, DT_SINGLELINE | DT_VCENTER | DT_CENTER);});
}
