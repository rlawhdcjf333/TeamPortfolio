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
	GameObject* temp;
	switch (mState)
	{
	case SelectState::BlueBan:
		//1. BlueBan : ChampListUI �����ְ�.. �ű洩���� �� è�� ��ǰ� ��, ���� Blue ���� ��ǻ�͸� ������
		temp = ChampToggle();
		if(temp)
			BData->ChampBan((Champ*)temp);
		if (BData->BanCount() == 1)
			NextState();
		break;
	case SelectState::RedBan:
		//2. RedBan : ���� ��������, �� �� è���� ���� �Ұ�
		temp = ChampToggle();
		if (temp)
			if (BData->GetBanOb(0) != temp)
				BData->ChampBan((Champ*)temp);
		if (BData->BanCount() == 2)
			NextState();
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
		mBackFrame->FrameRender(hdc, mButtonList[0].left, mButtonList[0].top, SetIndexX(mChampList[0]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[1].left, mButtonList[1].top, SetIndexX(mChampList[1]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[2].left, mButtonList[2].top, SetIndexX(mChampList[2]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[3].left, mButtonList[3].top, SetIndexX(mChampList[3]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[4].left, mButtonList[4].top, SetIndexX(mChampList[4]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[5].left, mButtonList[5].top, SetIndexX(mChampList[5]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[6].left, mButtonList[6].top, SetIndexX(mChampList[6]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[7].left, mButtonList[7].top, SetIndexX(mChampList[7]), 0);
		mBackFrame->FrameRender(hdc, mButtonList[8].left, mButtonList[8].top, SetIndexX(mChampList[8]), 0);
		//mBackFrame->FrameRender(hdc, mButtonList[9].left, mButtonList[9].top, SetIndexX(mChampList[9]), 0);

		//mBackFrame->FrameRender(hdc, 325, 615, 1, 0);
		BanRender(hdc, 325, 610, BData->GetBanCp(0));
		//mBackFrame->FrameRender(hdc, 880, 615, 1, 0);
		BanRender(hdc, 880, 610, BData->GetBanCp(1));

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
	GameObject* select = nullptr;
	GameObject* temp;
	//è���� 10���ΰɷ� �˰� ������
	temp = ToggleButton(0);
	if (temp)
		select = temp;
	temp = ToggleButton(1);
	if (temp)
		select = temp;
	temp = ToggleButton(2);
	if (temp)
		select = temp;
	temp = ToggleButton(3);
	if (temp)
		select = temp;
	temp = ToggleButton(4);
	if (temp)
		select = temp;
	temp = ToggleButton(5);
	if (temp)
		select = temp;
	temp = ToggleButton(6);
	if (temp)
		select = temp;
	temp = ToggleButton(7);
	if (temp)
		select = temp;
	temp = ToggleButton(8);
	if (temp)
		select = temp;
	//mToggleButton(9, "None", [this]() {});
	//if (temp)
	//	select = temp;
	return select;
}

GameObject* ChampSelect::ToggleButton(int index)
{
	if (PtInRect(&mButtonList[index], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {
			return mChampList[index];
		}
	}
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

void ChampSelect::BanRender(HDC hdc, int x, int y, Champ* champ)
{
	if (!champ)
		return;
	champ->UIRender(hdc, x + 2, y + 2, 70, 70);

	wstring champName = champ->GetChampName();
	RECT nameBox = RectMake(x, y + 74, 77, 30);
	CallFont(hdc, 12, [hdc, champName, &nameBox]() {DrawText(hdc, champName.c_str(), champName.size(), &nameBox, DT_SINGLELINE | DT_VCENTER | DT_CENTER); });
}
