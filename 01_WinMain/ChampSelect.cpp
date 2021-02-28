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
	LoadFromFile("ChampFrame");//0~9 : 챔프, 10~11 : 밴된 챔프
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
//블루 선밴 - 레드 후밴 - 블루 1픽 - 레드 1,2픽 - 블루 2,3픽 - 레드 3픽
	GameObject* temp;
	switch (mState)
	{
	case SelectState::BlueBan:
		//1. BlueBan : ChampListUI 보여주고.. 거길누르면 그 챔프 밴되게 함, 만약 Blue 팀이 컴퓨터면 랜덤밴
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

			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
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
		//2. RedBan : 위랑 마찬가지, 밴 된 챔프는 선택 불가
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
			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
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
		//3. BluePick1 : 플레이 할 챔프 1명 선택	->	클릭이 일어나면... 챔프 내부의 스테프 변수 설정?
		if (BData->GetPlayerTeam() == Team::Blue)
		{
			temp = ChampToggle();
			if (temp)
			{
				BData->ChampSelect(BData->GetSelectStaff(0),(Champ*)temp);
			}
		}
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0,8);//9마리
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
		//4. RedPick1,2 : 플레이 할 챔프 2명 선택
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
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
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
	//5. BluePick2,3 : 플레이 할 챔프 2명 선택
	case SelectState::BluePick2: case SelectState::BluePick3:
		//4. RedPick1,2 : 플레이 할 챔프 2명 선택
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
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
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
	//6. RedPick3 : 플레이 할 챔프 1명 선택
	case SelectState::RedPick3:
		if (BData->GetPlayerTeam() == Team::Red)
		{
			temp = ChampToggle();
			if (temp)
			{
				BData->ChampSelect(BData->GetSelectStaff(2), (Champ*)temp);
			}
		}
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;
			
			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
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
		//챔프 출력
		for (int i = 0; i < mChampList.size(); i++)
		{
			ChampRender(hdc, 232 + i * 80, 184, mChampList, i);
		}

		//4번째 인자인 x Frame은 Champ를 성공적으로 불러오면 SetIndexX(챔프의 포인터)를 넣어서 인덱스 세팅
		//예시 -> mBackFrame->FrameRender(hdc,mButtonList[0].left, mButtonList[0].top, SetIndexX(mChampList[0]),0);
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
	//챔프가 10개인걸로 알고 만들어둠
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
	// Team::None(팀 미정) = 0, Team::Ban(밴됨) = 1, Team::Bleu = 2, Team::Red = 3
}

void ChampSelect::NextState()
{
	mState = (SelectState)(1 + (int)mState);
	if (mState != SelectState::RedPick2 && mState != SelectState::BluePick3)//조건에 들어가는 단계들은 Guide UI가 변경되지않아야됨
	{
		BanPickGuide* tptr = (BanPickGuide*)ObjectManager::GetInstance()->FindObject("BanPickGuide");
		tptr->NextFrame();//BanPickGuide클래스 내부 함수...에 접근하려고 ↑에서 다운캐스팅
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
