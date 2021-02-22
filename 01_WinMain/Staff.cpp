#include "pch.h"
#include "Staff.h"
#include "Animation.h"

vector<string> Staff::Name;

Staff::Staff(const string& name, const wstring& fileName)
	:GameObject(name)
{
	mFileName = fileName;
	mIsActive = false;
}

void Staff::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;

	mStaffName = RandomName();
	mAtk = Random::GetInstance()->RandomInt(3, 7);
	mDef = Random::GetInstance()->RandomInt(3, 7);

	//champ들의 name중에서 랜덤 2개 < champ완성되거나 몇개 만들어지면 넣어야할듯?, 자료형 나중에 맞추지 뭐
	string champName = "챔프이름1";//champ이름 아무거나 뽑아오는 함수? < objectmanager에서 ObjectLayer::Champ인데에서 뽑아오는거 만들기, 
	mMostChamp.insert(make_pair(champName, 3));
	string champName2 = "챔프이름2";
	mMostChamp.insert(make_pair(champName2, 3));

	mChar1 = (Character)Random::GetInstance()->RandomInt(8);
	mChar2 = (Character)Random::GetInstance()->RandomInt(9);

	mTraningPoint = 0;

	mRandomIndexX = Random::GetInstance()->RandomInt(10);
	mRandomIndexY = Random::GetInstance()->RandomInt(8);

	IMAGEMANAGER->LoadFromFile(mFileName, Resources(mFileName + L".bmp"), 960, 512, 30, 16, true);
	mImage = IMAGEMANAGER->FindImage(mFileName);

	mRenderSizeX = mImage->GetFrameWidth() * 2;
	mRenderSizeY = mImage->GetFrameHeight() * 2;

	Animation* RightIdle = new Animation();
	RightIdle->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2, mRandomIndexX * 3, mRandomIndexY * 2, true);
	RightIdle->SetIsLoop(true);
	RightIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightIdle", RightIdle));
	mCurrentAnm = RightIdle;

	Animation* LeftIdle = new Animation();
	LeftIdle->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2 + 1, mRandomIndexX * 3, mRandomIndexY * 2 + 1, true);
	LeftIdle->SetIsLoop(true);
	LeftIdle->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftIdle", LeftIdle));

	Animation* RightRun = new Animation();
	RightRun->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2, mRandomIndexX * 3 + 2, mRandomIndexY * 2, true);
	RightRun->SetIsLoop(true);
	RightRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"RightRun", RightRun));

	Animation* LeftRun = new Animation();
	LeftRun->InitFrameByStartEnd(mRandomIndexX * 3, mRandomIndexY * 2 + 1, mRandomIndexX * 3 + 2, mRandomIndexY * 2 + 1, true);
	LeftRun->SetIsLoop(true);
	LeftRun->SetFrameUpdateTime(0.2f);
	mAnimationList.insert(make_pair(L"LeftRun", LeftRun));
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
	if (mIsActive)
	{
		mCurrentAnm->Update();
	}
}

void Staff::Render(HDC hdc)
{
	if (mIsActive)
	{
		mImage->ScaleFrameRender(hdc, mX, mY, mCurrentAnm->GetNowFrameX(), mCurrentAnm->GetNowFrameY(), mRenderSizeX, mRenderSizeY);
	}
}

void Staff::UIRender(HDC hdc, int startX, int startY, int width, int height)
{
	mImage->ScaleFrameRender(hdc, startX, startY, mRandomIndexX*3, mRandomIndexY*2, width, height);
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
		Name.push_back("Wa!");
		Name.push_back("Maple");
		Name.push_back("Mr.Kyungil");
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
		Name.push_back("Hwajin");
		Name.push_back("Igandir");
		Name.push_back("Iteric");
		Name.push_back("Jarrite");
		Name.push_back("Korten");
		Name.push_back("Synthesizer makes me feel high");
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