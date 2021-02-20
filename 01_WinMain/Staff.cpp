#include "pch.h"
#include "Staff.h"
#include "Animation.h"

vector<string> Staff::Name;

void Staff::Init()
{
	mName = RandomName();

	mAtk = Random::GetInstance()->RandomInt(20);
	mDef = Random::GetInstance()->RandomInt(20);

	//champ들의 name중에서 랜덤 2개 < champ완성되거나 몇개 만들어지면 넣어야할듯?, 자료형 나중에 맞추지 뭐
	wstring champName = L"챔프이름1";//champ이름 아무거나 뽑아오는 함수? < objectmanager에서 ObjectLayer::Champ인데에서 뽑아오는거 만들기, 
	mMostChamp.insert(make_pair(champName, 3));
	wstring champName2 = L"챔프이름2";
	mMostChamp.insert(make_pair(champName2, 3));

	mChar1 = (Character)Random::GetInstance()->RandomInt(8);
	mChar2 = (Character)Random::GetInstance()->RandomInt(9);

	mTraningPoint = 0;

	//mImage = IMAGEMANAGER->FindImage();	//랜덤하게 넣기
	
	//이미지 작업한 다음에 애니메이션 모션 만들어서 넣기
	/*
	Animation* tempAnm = new Animation();
	tempAnm->InitFrameByStartEnd(min, Y, max, Y, true);
	tempAnm->SetIsLoop(true);
	tempAnm->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", tempAnm));
	mCurrentAnm = tempAnm;
	*/
}

void Staff::Release()
{
	map<wstring, Animation*> :: iterator iter = mAnimationList.begin();
	for (; iter != mAnimationList.end(); ++iter) {
		SafeDelete(iter->second);
	}
}

void Staff::Update()
{
	//??뭘 업데이트 해야하지?
}

void Staff::Render(HDC hdc)
{
	//mImage->FrameRender(hdc, mX, mY, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY());
}

string Staff::RandomName()
{
	if (Name.size() == 0)
	{
		Name.push_back("KSW");
		Name.push_back("Banana");
		Name.push_back("Crom");
		Name.push_back("Jake");
		Name.push_back("Sam");
		Name.push_back("HobakGoguma");
		Name.push_back("Lockman");
		Name.push_back("Wa");
		Name.push_back("Maple");
		Name.push_back("Mr.Kyugil");
		Name.push_back("Ppangkkuttongkku");
		Name.push_back("Gonjaless");
		Name.push_back("Mario");
		Name.push_back("MG the God");
		Name.push_back("Takara");
		Name.push_back("Kakao");
		Name.push_back("Lion");
		Name.push_back("Zelda");
		Name.push_back("Github");
		Name.push_back("Donggass");
		Name.push_back("Erum");
		Name.push_back("Jerry");
		Name.push_back("Tom");
		Name.push_back("Kwangsub");
		Name.push_back("GHAAA");
		Name.push_back("Vecx");
		Name.push_back("NuguryMaster");
		Name.push_back("Bryndi");
		Name.push_back("Eksomess");
		Name.push_back("Gwawle");
		Name.push_back("Igandir");
		Name.push_back("Iteric");
		Name.push_back("Jarrite");
		Name.push_back("Korten");
		Name.push_back("cidy sizer makes my feel hight");
		Name.push_back("Umilum");
		Name.push_back("Webbitus");
		Name.push_back("Nugu");
		Name.push_back("Emetshelk");
		Name.push_back("Danice");
		Name.push_back("Edward Elic");
		Name.push_back("CommitPushij-jima");
		Name.push_back("Jumsimnagasumukulgugodhea");
		Name.push_back("Laliho");
		Name.push_back("Cloy");
		Name.push_back("Bob");
		Name.push_back("Brave Cookie");
		Name.push_back("Gardian");
		Name.push_back("Faker");
		Name.push_back("Last");
	}

	int index = Random::GetInstance()->RandomInt(Name.size());
	string name = Name[index];
	Name.erase(Name.begin()+index);
	return name;
}