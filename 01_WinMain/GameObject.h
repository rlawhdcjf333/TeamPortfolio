#pragma once
//조상님!!!
class GameObject
{
protected:
	string mName;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	RECT mRect;
	bool mIsActive;		//활성화 상태
	bool mIsDestroy;	//삭제할지 말지
public:
	GameObject();
	GameObject(const string& name);

	//순수가상함수 였던 것. 추상 클래스는 인스턴스를 생성할 수 없어서 순수가상함수로 만들 수 없음. (Storage 최초 등록에 필요함)
	//그르니까 얘 자손들은 이하 함수를 반드시 override ㄱ;
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

	inline bool GetIsActive()const { return mIsActive; }
	inline void SetIsActive(bool b) { mIsActive = b; }
	inline bool GetIsDestroy()const { return mIsDestroy; }
	inline void SetIsDestroy(bool b) { mIsDestroy = b; }

public:
	GameObject(const GameObject& copy); //복사 생성자 오버로딩 돈 터치
	GameObject& operator= (const GameObject& copy); //복사 연산자 오버로딩 건들지마라
};

