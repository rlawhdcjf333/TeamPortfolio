#include "pch.h"
#include "Director.h"
#include "Staff.h"

//vector<string> Director::Name;

Director::Director(const string& name, const wstring& fileName)
	:GameObject(name)
{
	mFileName = fileName;
	mIsActive = false;
}

// 굳이 감독 캐릭터가 필요할까??
// 팀이름
// TeamNuguri, TeamMansu, TeamJoyRoom, TeamCowHead
void Director::Init()
{

	IMAGEMANAGER->GetInstance()->LoadFromFile(mFileName, Resources(mFileName + L".bmp"), 60, 60, true);
	mTeamImage = IMAGEMANAGER->GetInstance()->FindImage(mFileName);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff(RandomName()));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff(RandomName()));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff(RandomName()));

	if (mName == "TeamNuguri") {
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff(RandomName()));
	}

	ObjectManager::GetInstance()->Init();
}

void Director::Release()
{
	SafeDelete(mTeamImage);
	ObjectManager::GetInstance()->Release();
}

void Director::Update()
{
	ObjectManager::GetInstance()->Update();
}

void Director::Render(HDC hdc)
{
	if (mIsActive) {
		mTeamImage->ScaleRender(hdc, mX, mY, mTeamImage->GetFrameWidth(), mTeamImage->GetFrameHeight());
		ObjectManager::GetInstance()->Render(hdc);
	}
}

string Director::RandomName()
{
	if (mNameList.size() == 0)
	{
		mNameList.push_back("KSW");
		mNameList.push_back("Banana");
		mNameList.push_back("Crom");
		mNameList.push_back("Jake");
		mNameList.push_back("Sam");
		mNameList.push_back("HobakGoguma");
		mNameList.push_back("Lockman");
		mNameList.push_back("Wa");
		mNameList.push_back("Maple");
		mNameList.push_back("Mr.Kyugil");
		mNameList.push_back("Ppangkkuttongkku");
		mNameList.push_back("Gonjaless");
		mNameList.push_back("Mario");
		mNameList.push_back("MG the God");
		mNameList.push_back("Takara");
		mNameList.push_back("Kakao");
		mNameList.push_back("Lion");
		mNameList.push_back("Zelda");
		mNameList.push_back("Github");
		mNameList.push_back("Donggass");
		mNameList.push_back("Erum");
		mNameList.push_back("Jerry");
		mNameList.push_back("Tom");
		mNameList.push_back("Kwangsub");
		mNameList.push_back("GHAAA");
		mNameList.push_back("Vecx");
		mNameList.push_back("NuguryMaster");
		mNameList.push_back("Bryndi");
		mNameList.push_back("Eksomess");
		mNameList.push_back("Gwawle");
		mNameList.push_back("Igandir");
		mNameList.push_back("Iteric");
		mNameList.push_back("Jarrite");
		mNameList.push_back("Korten");
		mNameList.push_back("cidy sizer makes my feel hight");
		mNameList.push_back("Umilum");
		mNameList.push_back("Webbitus");
		mNameList.push_back("Nugu");
		mNameList.push_back("Emetshelk");
		mNameList.push_back("Danice");
		mNameList.push_back("Edward Elic");
		mNameList.push_back("CommitPushij-jima");
		mNameList.push_back("Jumsimnagasumukulgugodhea");
		mNameList.push_back("Laliho");
		mNameList.push_back("Cloy");
		mNameList.push_back("Bob");
		mNameList.push_back("Brave Cookie");
		mNameList.push_back("Gardian");
		mNameList.push_back("Faker");
		mNameList.push_back("Last");
	}

	int index = Random::GetInstance()->RandomInt(mNameList.size());
	string name = mNameList[index];
	mNameList.erase(mNameList.begin() + index);
	return name;
}