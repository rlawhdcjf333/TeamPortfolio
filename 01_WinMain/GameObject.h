#pragma once
//�����!!!
class GameObject
{
protected:
	string mName;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	//float mAtk;
	RECT mRect;
	RECT mHitBox;
	RECT mAttackRect;
	bool mIsActive;		//Ȱ��ȭ ����
	bool mIsDestroy;	//�������� ����
public:
	GameObject();
	GameObject(const string& name);

	//���������Լ� ���� ��. �߻� Ŭ������ �ν��Ͻ��� ������ �� ��� ���������Լ��� ���� �� ����. (Storage ���� ��Ͽ� �ʿ���)
	//�׸��ϱ� �� �ڼյ��� ���� �Լ��� �ݵ�� override ��;
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
public:
	inline string GetName()const { return mName; }
	inline void SetName(const string& name) { mName = name; }
	inline float GetX()const { return mX; }
	inline void SetX(float x) { mX = x; }
	inline float GetY()const { return mY; }
	inline void SetY(float y) { mY = y; }
	inline float GetSizeX()const { return mSizeX; }
	inline void SetSizeX(float x) { mSizeX = x; }
	inline float GetSizeY()const { return mSizeY; }
	inline void SetSizeY(float y) { mSizeY = y; }
	inline RECT GetRect()const { return mRect; }
	inline RECT GetHitBox()const { return mHitBox; }
	RECT GetAttackRect() { return mAttackRect; }

	inline bool GetIsActive()const { return mIsActive; }
	inline void SetIsActive(bool b) { mIsActive = b; }
	inline bool GetIsDestroy()const { return mIsDestroy; }
	inline void SetIsDestroy(bool b) { mIsDestroy = b; }
};

