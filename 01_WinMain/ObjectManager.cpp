#include "pch.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Director.h"
#include "Staff.h"

ObjectManager::ObjectManager()
{
	for (int i = 0; i < (int)ObjectLayer::End; ++i)
	{
		vector<GameObject*> emptyVector;
		mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
	}
}


void ObjectManager::Init()
{
	ObjectIter iter = mObjectList.begin();
	
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Init();
			
			if (iter->first == ObjectLayer::Director)
			{
				if (Storage::GetInstance()->FindObject(iter->second[i]->GetName()) != nullptr) // 저장소에 같은 이름으로 된 데이터가 존재하면
				{
					GameObject* tmp = Storage::GetInstance()->FindObject(iter->second[i]->GetName());
					OriginSwap(ObjectLayer::Director, tmp); //스왑

					Director * tmpdir = (Director*)iter->second[i];
					for (string elem : tmpdir->GetStaffNameList())
					{
						mObjectList[ObjectLayer::Staff].push_back(new Staff(elem, elem, tmpdir->GetTeamName()));
					}
				}
			}

			if (iter->first == ObjectLayer::Staff)
			{
				if (Storage::GetInstance()->FindObject(iter->second[i]->GetName()) != nullptr) // 저장소에 같은 이름으로 된 데이터가 존재하면
				{
					GameObject* tmp = Storage::GetInstance()->FindObject(iter->second[i]->GetName());
					OriginSwap(ObjectLayer::Staff, tmp); // 스왑
				}
			}
		}
	}

	Storage::GetInstance()->CopyToStorage(mObjectList);

}

void ObjectManager::Release()
{
	ObjectIter iter = mObjectList.begin();
	Storage::GetInstance()->CopyToStorage(mObjectList);

	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);
		}

		iter->second.clear();
		iter->second.shrink_to_fit();
	}
	
}

void ObjectManager::Update()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsDestroy() == true)
			{
				iter->second[i]->Release();
				SafeDelete(iter->second[i]);
				iter->second.erase(iter->second.begin() + i);
				--i;
				continue;
			}
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Update();
			}
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Render(hdc);
			}
		}
	}
}

void ObjectManager::AddObject(ObjectLayer layer, GameObject * object)
{
	mObjectList[layer].push_back(object);
}

GameObject * ObjectManager::FindObject(const string & name)
{
	ObjectIter iter = mObjectList.begin();

	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				return iter->second[i];
			}
		}
	}
	return nullptr;
}

GameObject * ObjectManager::FindObject(ObjectLayer layer, const string & name)
{
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			return iter->second[i];
		}
	}
	return nullptr;
}

vector<class GameObject*> ObjectManager::FindObjects(const string & name)
{
	vector<GameObject*> result;

	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				result.push_back(iter->second[i]);
			}
		}
	}

	return result;
}

vector<class GameObject*> ObjectManager::FindObjects(ObjectLayer layer, const string & name)
{
	vector<GameObject*> result;
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			result.push_back(iter->second[i]); 
		}
	}
	return result;
}

vector<class GameObject*> ObjectManager::GetObjectList(ObjectLayer layer)
{
	return mObjectList[layer];
}

void ObjectManager::OriginSwap(ObjectLayer layerName, GameObject * old)
{

	auto& tmp = mObjectList[layerName];

	for (GameObject*& elem : tmp)
	{
		if (elem->GetName() == old->GetName())
		{
			elem->Release();
			SafeDelete(elem); //비워주고

			if (layerName == ObjectLayer::Director)
			{
				Director* pTmp = (Director*) old; // 다운캐스팅
				Director *copy = new Director(*pTmp); // 복사 ㄱㄱ
			
				elem = copy;
				
			}
		
			if (layerName == ObjectLayer::Staff)
			{
				Staff* pTmp = (Staff*)old; // 다운캐스팅
				Staff *copy = new Staff(*pTmp); // 복사 ㄱㄱ

				elem = copy;

			}
		}
	}
		
}






