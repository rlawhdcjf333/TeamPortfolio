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

	mChampList = ChampManager::GetInstance()->GetChampList();
	mCurrentChamp = nullptr;

	DelayReset();
}

void ChampSelect::Release()
{
}

void ChampSelect::Update()
{
	mChampList = ChampManager::GetInstance()->GetChampList();
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
				BData->ChampBan((Champ*)temp), DelayReset();
		}
		else
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
			if (BData->IsSelectChamp((Champ*)mChampList[index]) == false)
				BData->ChampBan((Champ*)mChampList[index]);
			
		}
		if (BData->BanCount() == 1)
		{
			SOUNDPLAYER->Play(L"Pick", 0.2f);
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
					BData->ChampBan((Champ*)temp), DelayReset();
		}
		else
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;
			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
			if(BData->IsSelectChamp((Champ*)mChampList[index]) == false)
				BData->ChampBan((Champ*)mChampList[index]);
			
		}
		if (BData->BanCount() == 2)
		{
			SOUNDPLAYER->Play(L"Pick", 0.2f);
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
				if (BData->IsSelectChamp((Champ*)temp) == false)
					BData->ChampSelect(BData->GetSelectStaff(0),(Champ*)temp), DelayReset();
			}
		}
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0,8);//9마리
			if (BData->IsSelectChamp((Champ*)mChampList[index]) == false)
				BData->ChampSelect(BData->GetEnemyStaff(0),(Champ*) mChampList[index]);
		}
		if (BData->GetSelectSize() == 1)
		{
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
				{
					if (BData->IsSelectChamp((Champ*)temp) == false)
					{
						 BData->ChampSelect(BData->GetSelectStaff(0), (Champ*)temp), DelayReset();
					}
				}
				else if (BData->GetSelectSize() == 2)
				{
					if (BData->IsSelectChamp((Champ*)temp) == false)
					{
						BData->ChampSelect(BData->GetSelectStaff(1), (Champ*)temp), DelayReset();
					}
				}
			}
		}
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
			if (BData->GetSelectSize() == 1)
			{
				if (BData->IsSelectChamp((Champ*)mChampList[index]) == false)
					BData->ChampSelect(BData->GetEnemyStaff(0), (Champ*)mChampList[index]), DelayReset();

				
			}
			else if (BData->GetSelectSize() == 2)
				if (BData->IsSelectChamp((Champ*)mChampList[index]) == false)
				{
					BData->ChampSelect(BData->GetEnemyStaff(1), (Champ*)mChampList[index]);
					SOUNDPLAYER->Play(L"Pick", 0.4f), DelayReset();
				}
		}
		if (BData->GetSelectSize() == 3)
		{
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
					BData->ChampSelect(BData->GetSelectStaff(1), (Champ*)temp), DelayReset();
				else if (BData->GetSelectSize() == 4)
					BData->ChampSelect(BData->GetSelectStaff(2), (Champ*)temp), DelayReset();
			}

		}
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;

			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
			if (BData->GetSelectSize() == 3)
			{
				if (BData->IsSelectChamp((Champ*)mChampList[index]) == false)
					BData->ChampSelect(BData->GetEnemyStaff(1), (Champ*)mChampList[index]), DelayReset();
				
			}
			else if (BData->GetSelectSize() == 4)
				if (BData->IsSelectChamp((Champ*)mChampList[index]) == false)
					BData->ChampSelect(BData->GetEnemyStaff(2), (Champ*)mChampList[index]), DelayReset();

		}
		if (BData->GetSelectSize() == 5)
		{
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
				if (BData->IsSelectChamp((Champ*)temp) == false)
					BData->ChampSelect(BData->GetSelectStaff(2), (Champ*)temp), DelayReset();
			}
		}
		else//플레이어 팀이 아닐경우 자동 픽
		{
			mDelay -= Time::GetInstance()->DeltaTime();
			if (mDelay > 0) return;
			
			int index = Random::GetInstance()->RandomInt(0, 8);//9마리
			if (BData->IsSelectChamp((Champ*)mChampList[index]) == false)
				BData->ChampSelect(BData->GetEnemyStaff(2), (Champ*)mChampList[index]), DelayReset();
			
		}
		if (BData->GetSelectSize() == 6)
		{
			DelayReset();
			NextState();
		}
		break;
	case SelectState::end: default:
		mCurrentChamp = nullptr;
		mState = SelectState::BlueBan;
		break;
	}

	mCurrentChamp = nullptr;
	for (int i = 0; i < mChampList.size(); i++)
	{
		if (PtInRect(&mButtonList[i], _mousePosition))
		{
			mCurrentChamp = (Champ*)mChampList[i];
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
		mBackFrame->AlphaFrameRender(hdc, mButtonList[0].left, mButtonList[0].top, SetIndexX(mChampList[0]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[1].left, mButtonList[1].top, SetIndexX(mChampList[1]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[2].left, mButtonList[2].top, SetIndexX(mChampList[2]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[3].left, mButtonList[3].top, SetIndexX(mChampList[3]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[4].left, mButtonList[4].top, SetIndexX(mChampList[4]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[5].left, mButtonList[5].top, SetIndexX(mChampList[5]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[6].left, mButtonList[6].top, SetIndexX(mChampList[6]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[7].left, mButtonList[7].top, SetIndexX(mChampList[7]), 0, 0.5f);
		mBackFrame->AlphaFrameRender(hdc, mButtonList[8].left, mButtonList[8].top, SetIndexX(mChampList[8]), 0, 0.5f);
		//mBackFrame->FrameRender(hdc, mButtonList[9].left, mButtonList[9].top, SetIndexX(mChampList[9]), 0);

		ChampInfoRender(hdc, mCurrentChamp);

		//mBackFrame->FrameRender(hdc, 325, 615, 1, 0);
		if (BData->GetBanCp(0) != nullptr)
		{
			BanRender(hdc, 325, 610, BData->GetBanCp(0));
		}
		//mBackFrame->FrameRender(hdc, 880, 615, 1, 0);
		if (BData->GetBanCp(1) != nullptr)
		{
			BanRender(hdc, 880, 610, BData->GetBanCp(1));
		}

		MouseOver(hdc);
	}
}

GameObject* ChampSelect::ChampToggle()
{
	GameObject* select = nullptr;
	GameObject* temp = nullptr;
	//챔프가 10개인걸로 알고 만들어둠
	temp = ToggleButton(0);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(1);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(2);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(3);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(4);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(5);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(6);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(7);
	if (temp)
	{
		select = temp;
	}
	temp = ToggleButton(8);
	if (temp)
	{
		select = temp;
	}
	//mToggleButton(9, "None", [this]() {});
	//if (temp)
	//	select = temp;
	return select;
}

GameObject* ChampSelect::ToggleButton(int index)
{
	if (PtInRect(&mButtonList[index], _mousePosition)) {

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			SOUNDPLAYER->Play(L"Pick", 0.2f);
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

void ChampSelect::ClearCurrentChamp()
{
	mCurrentChamp = nullptr;
}

void ChampSelect::ChampInfoRender(HDC hdc, Champ* champ)
{
	if (champ)
	{
		champ->UIRender(hdc, 235, 438, 95, 80);
	
		wstring champName = champ->GetChampName();
		RECT nameBox = RectMake(234,519,98,30);
		CallFont(hdc, 20, [&nameBox, champName, hdc]() {DrawText(hdc, champName.c_str(), champName.size(), &nameBox, DT_CENTER|DT_VCENTER|DT_SINGLELINE);});

		wstring atk = (to_wstring)((int)champ->GetAtk());
		RECT atkBox = RectMake(454, 416, 87, 22);
		wstring def = (to_wstring)((int)champ->GetDef());
		RECT defBox = RectMake(454, 444, 87, 22);
		wstring heal = (to_wstring)((int)champ->GetHealPr());
		RECT healBox = RectMake(454, 472, 87, 22);
		wstring range = (to_wstring)((int)champ->GetRange());
		RECT rangeBox = RectMake(454, 500, 87, 22);
		wstring speed = (to_wstring)((int)champ->GetSpeed());
		RECT speedBox = RectMake(454, 528, 87, 22);

		CallFont(hdc, 20, [atk, &atkBox, hdc]() {DrawText(hdc, atk.c_str(), atk.size(), &atkBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});
		CallFont(hdc, 20, [def, &defBox, hdc]() {DrawText(hdc, def.c_str(), def.size(), &defBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});
		CallFont(hdc, 20, [heal, &healBox, hdc]() {DrawText(hdc, heal.c_str(), heal.size(), &healBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});
		CallFont(hdc, 20, [range, &rangeBox, hdc]() {DrawText(hdc, range.c_str(), range.size(), &rangeBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});
		CallFont(hdc, 20, [speed, &speedBox, hdc]() {DrawText(hdc, speed.c_str(), speed.size(), &speedBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);});

		RECT skillrc = RectMake(556, 423, 50, 50);
		champ->SkillImageRender(hdc, skillrc);
		wstring skillCool = to_wstring((int)champ->GetSkillCool());
		RECT scBox = RectMake(633, 452, 55, 20);
		CallFont(hdc, 20, [skillCool, hdc, &scBox]() {DrawText(hdc, skillCool.c_str(), skillCool.size(), &scBox, DT_CENTER|DT_VCENTER|DT_SINGLELINE);});

		RECT ultrc = RectMake(556, 493, 50, 50);
		champ->SpecialSkillImageRender(hdc, ultrc);
		wstring ultCool = L"Full Mana";
		RECT ultBox = RectMake(633, 520, 55, 20);
		CallFont(hdc, 15, [ultCool, hdc, &ultBox]() {DrawText(hdc, ultCool.c_str(), ultCool.size(), &ultBox, DT_CENTER|DT_VCENTER|DT_SINGLELINE);});

		wstring skillex = champ->GetSkillEx();
		RECT exBox = RectMake(720, 423, 300, 50);
		CallFont(hdc, 15, [skillex, &exBox, hdc]() {DrawText(hdc, skillex.c_str(), skillex.size(), &exBox, DT_WORDBREAK|DT_LEFT);});

		wstring ultex = champ->GetSpecialSkillEx();
		RECT ultexBox = RectMake(720, 493, 300, 50);
		CallFont(hdc, 15, [ultex, &ultexBox, hdc]() {DrawText(hdc, ultex.c_str(), ultex.size(), &ultexBox, DT_WORDBREAK | DT_LEFT);});

	}







}