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

}

void ChampSelect::Release()
{
}

void ChampSelect::Update()
{
//블루 선밴 - 레드 후밴 - 블루 1픽 - 레드 1,2픽 - 블루 2,3픽 - 레드 3픽
	switch (mState)
	{
	case SelectState::BlueBan:
		//1. BlueBan : ChampListUI 보여주고.. 거길누르면 그 챔프 밴되게 함, 만약 Blue 팀이 컴퓨터면 랜덤밴
		//BData->ChampBan((Champ*)ChampToggle());
		//if (BData->BanCount() == 1)
		//	NextState();
		break;
	case SelectState::RedBan:
		//2. RedBan : 위랑 마찬가지, 밴 된 챔프는 선택 불가
		//GameObject* temp;
		//temp = ChampToggle();
		//if (BData->GetBan(0) != temp)
		//	BData->ChampBan((Champ*)temp);
		//if (BData->BanCount() == 2)
		//	NextState();
		break;
	//3. BluePick1 : 플레이 할 챔프 1명 선택	->	클릭이 일어나면... 챔프 내부의 스테프 변수 설정?
	//4. RedPick2 : 플레이 할 챔프 2명 선택
	//5. BluePick2 : 플레이 할 챔프 2명 선택
	//6. RedPick2 : 플레이 할 챔프 1명 선택
	//7. 위 과정이 끝나면 ChampCheckUI활성 + 플레이어의 팀 스태프끼리 챔피언을 바꿀 수 있는 시간이 주어지고,
	}
}

void ChampSelect::Render(HDC hdc)
{
	if (mIsActive)
	{
		//4번째 인자인 x Frame은 Champ를 성공적으로 불러오면 SetIndexX(챔프의 포인터)를 넣어서 인덱스 세팅
		//예시 -> mBackFrame->FrameRender(hdc,mButtonList[0].left, mButtonList[0].top, SetIndexX(mChampList[0]),0);
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

		mBackFrame->FrameRender(hdc, 600, 300, 1, 0);//벤 프레임은 고정이니깐 1
		mBackFrame->FrameRender(hdc, 600, 980, 1, 0);

		//챔프 출력
		for (int i = 0; i < mChampList.size(); i++)
		{
			ChampRender(hdc, 232 + i * 80, 182, mChampList, i);
		}

		MouseOver(hdc);
	}
}

GameObject* ChampSelect::ChampToggle()
{
	//챔프가 10개인걸로 알고 만들어둠
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
	// Team::None(팀 미정) = 0, Team::Ban(밴됨) = 1, Team::Bleu = 2, Team::Red = 3
}

void ChampSelect::NextState()
{
	mState = (SelectState)(1 + (int)mState);
	if (mState != SelectState::RedPick1 && mState != SelectState::BluePick2)//조건에 들어가는 단계들은 Guide UI가 변경되지않아야됨
	{
		BanPickGuide* tptr = (BanPickGuide*)ObjectManager::GetInstance()->FindObject("BanPickGuide");
		tptr->NextFrame();//BanPickGuide클래스 내부 함수...에 접근하려고 ↑에서 다운캐스팅
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
