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
		}
	}

	for (; iter != mObjectList.end(); iter++)
	{
		if (iter->first == ObjectLayer::Director)
		{
			for (int i = 0; i < iter->second.size(); ++i) {

				if (Storage::GetInstance()->FindObject(iter->second[i]->GetName()) != nullptr) // ����ҿ� ���� �̸����� �� �����Ͱ� �����ϸ�
				{
					OriginSwap(ObjectLayer::Director, Storage::GetInstance()->FindObject(iter->second[i]->GetName()));
				}
			}

		}

		if (iter->first == ObjectLayer::Staff)
		{
			for (int i = 0; i < iter->second.size(); ++i) {
				if (Storage::GetInstance()->FindObject(iter->second[i]->GetName()) != nullptr) // ����ҿ� ���� �̸����� �� �����Ͱ� �����ϸ�
				{
					OriginSwap(ObjectLayer::Staff, Storage::GetInstance()->FindObject(iter->second[i]->GetName()));
				}
			}
		}
	}
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
	//map�� �迭�����ڰ� ���ǵǾ� �ִ�. 
	//��, ���� �迭ó�� �����ϴ°� �ƴ϶�.[]������ ���ο� find�Լ��� �Ἥ ������
	//�׷��� �ᱹ find���°Ŷ� ����ѵ�, �ٸ����̶�� �Ѵٸ� �ش� Ű���� �����Ͱ� 
	//������ ���� �����ع���. �����ؾ���

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

void ObjectManager::OriginSwap(ObjectLayer layerName, GameObject * newPtr)
{
	ObjectIter iter = mObjectList.begin();

	auto& tmp = mObjectList[layerName];

	for (GameObject*& elem : tmp)
	{
		if (elem->GetName() == newPtr->GetName())
		{
			if (layerName == ObjectLayer::Director)
			{
				Director* pTmp = (Director*) newPtr; // �ٿ�ĳ����
				Director copy = *pTmp; // ���� ����

				elem->Release();
				SafeDelete(elem);
				elem = &copy;

			}
		
			if (layerName == ObjectLayer::Staff)
			{
				Staff* pTmp = (Staff*)newPtr; // �ٿ�ĳ����
				Staff copy = *pTmp; // ���� ����

				elem->Release();
				SafeDelete(elem);
				elem = &copy;

			}
		}
	}
		
}






