#pragma once

/*
## ObjectManager ##
GameObject �����ϴ� Ŭ����
*/

//enum (������) : ������ �ٸ� �̸����� ǥ���ϴ� ��
enum class ObjectLayer : int
{
	Background = 0, 
	Director = 1,
	Staff = 2,
	Champ = 3,
	UI = 4,
	End
};

class ObjectManager
{
	Singleton(ObjectManager)
protected:
	typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectLayer, vector<class GameObject*>> mObjectList;
public:
	ObjectManager();

	void Init();
	void LoadInit();
	void Release();
	void Update();
	void Render(HDC hdc);

	virtual void AddObject(ObjectLayer layer, class GameObject* object);
	virtual class GameObject* FindObject(const string& name);
	virtual class GameObject* FindObject(ObjectLayer layer, const string& name);
	virtual vector<class GameObject*> FindObjects(const string& name);
	virtual vector<class GameObject*> FindObjects(ObjectLayer layer, const string& name);
	virtual vector<class GameObject*> GetObjectList(ObjectLayer layer);

	void OriginSwap(ObjectLayer layerName, GameObject* old);

	void Zorder();
};

