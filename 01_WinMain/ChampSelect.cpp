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

	DelayReset();
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
		if (BData->GetPlayerTeam() == Team::Blue)
		{
			temp = ChampToggle();
			if (temp)
				BData->ChampBan((Champ*)temp);
		}
		else
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9����
			BData->ChampBan((Champ*)mChampList[index]);
			
		}
		if (BData->BanCount() == 1)
		{
			SOUNDPLAYER->Play(L"Pick", 0.4f);
			DelayReset();
			NextState();
		}
		break;
	case SelectState::RedBan:
		//2. RedBan : ���� ��������, �� �� è���� ���� �Ұ�
		if (BData->GetPlayerTeam() == Team::Red)
		{
			temp = ChampToggle();
			if (temp)
				if (BData->GetBanOb(0) != temp)
					BData->ChampBan((Champ*)temp);
		}
		else
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;
			int index = Random::GetInstance()->RandomInt(0, 8);//9����
			BData->ChampBan((Champ*)mChampList[index]);
			
		}
		if (BData->BanCount() == 2)
		{
			SOUNDPLAYER->Play(L"Pick", 0.4f);
			DelayReset();
			NextState();
		}
		break;
	case SelectState::BluePick1:
		//3. BluePick1 : �÷��� �� è�� 1�� ����	->	Ŭ���� �Ͼ��... è�� ������ ������ ���� ����?
		if (BData->GetPlayerTeam() == Team::Blue)
		{
			temp = ChampToggle();
			if (temp)
			{
				BData->ChampSelect(BData->GetSelectStaff(0),(Champ*)temp);
			}
		}
		else//�÷��̾� ���� �ƴҰ�� �ڵ� ��
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0,8);//9����
			BData->ChampSelect(BData->GetEnemyStaff(0),(Champ*) mChampList[index]);
		}
		if (BData->GetSelectSize() == 1)
		{
			SOUNDPLAYER->Play(L"Pick", 0.4f);
			DelayReset();
			NextState();
		}
		break;
	case SelectState::RedPick1: case SelectState::RedPick2:
		//4. RedPick1,2 : �÷��� �� è�� 2�� ����
		if (BData->GetPlayerTeam() == Team::Red)
		{
			temp = ChampToggle();
			if (temp)
			{
				if (BData->GetSelectSize() == 1)
					BData->ChampSelect(BData->GetSelectStaff(0), (Champ*)temp);
				else if (BData->GetSelectSize() == 2)
					BData->ChampSelect(BData->GetSelectStaff(1), (Champ*)temp);
			}

		}
		else//�÷��̾� ���� �ƴҰ�� �ڵ� ��
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9����
			if (BData->GetSelectSize() == 1)
			{
				BData->ChampSelect(BData->GetEnemyStaff(0), (Champ*)mChampList[index]);

				if (BData->GetSelectSize() == 2)
				{
					SOUNDPLAYER->Play(L"Pick", 0.4f), DelayReset(); return;
				}
			}
			else if (BData->GetSelectSize() == 2)
				BData->ChampSelect(BData->GetEnemyStaff(1), (Champ*)mChampList[index]), SOUNDPLAYER->Play(L"Pick", 0.4f), DelayReset();
		}
		if (BData->GetSelectSize() == 3)
		{
			SOUNDPLAYER->Play(L"Pick", 0.4f);
			DelayReset();
			NextState();
		}
		break;
	//5. BluePick2,3 : �÷��� �� è�� 2�� ����
	case SelectState::BluePick2: case SelectState::BluePick3:
		//4. RedPick1,2 : �÷��� �� è�� 2�� ����
		if (BData->GetPlayerTeam() == Team::Blue)
		{
			temp = ChampToggle();
			if (temp)
			{
				if (BData->GetSelectSize() == 3)
					BData->ChampSelect(BData->GetSelectStaff(1), (Champ*)temp);
				else if (BData->GetSelectSize() == 4)
					BData->ChampSelect(BData->GetSelectStaff(2), (Champ*)temp);
			}

		}
		else//�÷��̾� ���� �ƴҰ�� �ڵ� ��
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9����
			if (BData->GetSelectSize() == 3)
			{
				BData->ChampSelect(BData->GetEnemyStaff(1), (Champ*)mChampList[index]);
				if (BData->GetSelectSize() == 4)
				{
					SOUNDPLAYER->Play(L"Pick", 0.4f), DelayReset(); return;
				}
			}
			else if (BData->GetSelectSize() == 4)
				BData->ChampSelect(BData->GetEnemyStaff(2), (Champ*)mChampList[index]), SOUNDPLAYER->Play(L"Pick", 0.4f), DelayReset();

		}
		if (BData->GetSelectSize() == 5)
		{
			SOUNDPLAYER->Play(L"Pick", 0.4f);
			DelayReset();
			NextState();
		}
		break;
	//6. RedPick3 : �÷��� �� è�� 1�� ����
	case SelectState::RedPick3:
		if (BData->GetPlayerTeam() == Team::Red)
		{
			temp = ChampToggle();
			if (temp)
			{
				BData->ChampSelect(BData->GetSelectStaff(2), (Champ*)temp);
			}
		}
		else//�÷��̾� ���� �ƴҰ�� �ڵ� ��
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;
			
			int index = Random::GetInstance()->RandomInt(0, 8);//9����
			BData->ChampSelect(BData->GetEnemyStaff(2), (Champ*)mChampList[index]);
			
		}
		if (BData->GetSelectSize() == 6)
		{
			SOUNDPLAYER->Play(L"Pick", 0.4f);
			DelayReset();
			NextState();
		}
	}
}

void ChampSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		//è�� ���
		for (int i = 0; i < mChampList.size(); i++)
		{
			ChampRender(hdc, 232 + i * 80, 184, mChampList, i);
		}

		//4��° ������ x Frame�� Champ�� ���������� �ҷ����� SetIndexX(è���� ������)�� �־ �ε��� ����
		//���� -> mBackFrame->FrameRender(hdc,mButtonList[0].left, mButtonList[0].top, SetIndexX(mChampList[0]),0);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[0].left, mButtonList[0].top, SetIndexX(mChampList[0]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[1].left, mButtonList[1].top, SetIndexX(mChampList[1]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[2].left, mButtonList[2].top, SetIndexX(mChampList[2]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[3].left, mButtonList[3].top, SetIndexX(mChampList[3]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[4].left, mButtonList[4].top, SetIndexX(mChampList[4]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[5].left, mButtonList[5].top, SetIndexX(mChampList[5]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[6].left, mButtonList[6].top, SetIndexX(mChampList[6]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[7].left, mButtonList[7].top, SetIndexX(mChampList[7]), 0, 0.3f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[8].left, mButtonList[8].top, SetIndexX(mChampList[8]), 0, 0.3f);
		//mBackFrame->FrameRender(hdc, mButtonList[9].left, mButtonList[9].top, SetIndexX(mChampList[9]), 0);

		//mBackFrame->FrameRender(hdc, 325, 615, 1, 0);
		BanRender(hdc, 325, 610, BData->GetBanCp(0));
		//mBackFrame->FrameRender(hdc, 880, 615, 1, 0);
		BanRender(hdc, 880, 610, BData->GetBanCp(1));

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

			SOUNDPLAYER->Play(L"Pick", 0.4f);
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
	if (mState != SelectState::RedPick2 && mState != SelectState::BluePick3)//���ǿ� ���� �ܰ���� Guide UI�� ��������ʾƾߵ�
	{
		BanPickGuide* tptr = (BanPickGuide*)ObjectManager::GetInstance()->FindObject("BanPickGuide");
		tptr->NextFrame();//BanPickGuideŬ���� ���� �Լ�...�� �����Ϸ��� �迡�� �ٿ�ĳ����
	}
}

void ChampSelect::ChampRender(HDC hdc, int x , int y, vector<GameObject*> list, int i)
{
	RECT outBox = RectMake(x, y, 77, 104);
	CallBrush(hdc, RGB(16, 18, 22), [hdc, outBox]() {RenderRect(hdc, outBox);});

	RECT inBox = RectMake(x + 2, y + 2, 70, 70);
	CallBrush(hdc, RGB(55, 57, 61), [hdc, inBox]() {RenderRect(hdc, inBox);});

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
