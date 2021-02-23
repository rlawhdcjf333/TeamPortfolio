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

	for (int i = 0; i < 3; i++) {
		mStaffNameList.push_back(RandomName());
	}
	
	if (mName == "TeamNuguri") {
		mStaffNameList.push_back(RandomName());
	}

	for (string name : mStaffNameList)
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff(name, mName));
	// Staff 클래스의 생성자를 확인하기 바랍니다. -CTO
	
	//for (string name : mStaffNameList) {
	//	ObjectManager::GetInstance()->FindObject(name)->Init();
	//}
	// AddObject돌리셨으면 굳이 Init() 돌릴 필요가 음슴니다. scene init에서 일괄적으로 돌리기 때문이죠. 이러면 Init()이 두번 돕니다 -CTO

	//ObjectManager::GetInstance()->FindObject(str1)->Init();
	//ObjectManager::GetInstance()->FindObject(str2)->Init();
	//ObjectManager::GetInstance()->FindObject(str3)->Init();
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
	if (mRandomNameList.size() == 0)
	{
		mRandomNameList.push_back("KSW");
		mRandomNameList.push_back("Banana");
		mRandomNameList.push_back("Crom");
		mRandomNameList.push_back("Jake");
		mRandomNameList.push_back("Sam");
		mRandomNameList.push_back("HobakGoguma");
		mRandomNameList.push_back("Lockman");
		mRandomNameList.push_back("Wa");
		mRandomNameList.push_back("Maple");
		mRandomNameList.push_back("Mr.Kyugil");
		mRandomNameList.push_back("Ppangkkuttongkku");
		mRandomNameList.push_back("Gonjaless");
		mRandomNameList.push_back("Mario");
		mRandomNameList.push_back("MG the God");
		mRandomNameList.push_back("Takara");
		mRandomNameList.push_back("Kakao");
		mRandomNameList.push_back("Lion");
		mRandomNameList.push_back("Zelda");
		mRandomNameList.push_back("Github");
		mRandomNameList.push_back("Donggass");
		mRandomNameList.push_back("Erum");
		mRandomNameList.push_back("Jerry");
		mRandomNameList.push_back("Tom");
		mRandomNameList.push_back("Kwangsub");
		mRandomNameList.push_back("GHAAA");
		mRandomNameList.push_back("Vecx");
		mRandomNameList.push_back("NuguryMaster");
		mRandomNameList.push_back("Bryndi");
		mRandomNameList.push_back("Eksomess");
		mRandomNameList.push_back("Gwawle");
		mRandomNameList.push_back("Igandir");
		mRandomNameList.push_back("Iteric");
		mRandomNameList.push_back("Jarrite");
		mRandomNameList.push_back("Korten");
		mRandomNameList.push_back("cidy sizer makes my feel hight");
		mRandomNameList.push_back("Umilum");
		mRandomNameList.push_back("Webbitus");
		mRandomNameList.push_back("Nugu");
		mRandomNameList.push_back("Emetshelk");
		mRandomNameList.push_back("Danice");
		mRandomNameList.push_back("Edward Elic");
		mRandomNameList.push_back("CommitPushij-jima");
		mRandomNameList.push_back("Jumsimnagasumukulgugodhea");
		mRandomNameList.push_back("Laliho");
		mRandomNameList.push_back("Cloy");
		mRandomNameList.push_back("Bob");
		mRandomNameList.push_back("Brave Cookie");
		mRandomNameList.push_back("Gardian");
		mRandomNameList.push_back("Faker");
		mRandomNameList.push_back("Last");
	}

	int index = Random::GetInstance()->RandomInt(mRandomNameList.size());
	string name = mRandomNameList[index];
	mRandomNameList.erase(mRandomNameList.begin() + index);
	return name;
}