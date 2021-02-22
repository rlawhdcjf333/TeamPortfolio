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

	//for (string name : mStaffNameList)
	//	ObjectManager::GetInstance()->AddObject(ObjectLayer::Staff, new Staff(name, mName));
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