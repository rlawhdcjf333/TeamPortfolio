#pragma once
#include "GameObject.h"
class Animation;
class Champ : public GameObject
{
protected:
	Image* mImage;
	Animation* mCurrentAnm;

	GameObject* mEnemy1;
	GameObject* mEnemy2;
	GameObject* mEnemy3;

	GameObject* mFriend1;
	GameObject* mFriend2;
	
	float mHP;
	float mMP;
	float mAtk;
	float mDef;
	

	float mAlpha;
	

public:
	Champ(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	
	virtual void SetEnemy(string enemy1, string enemy2, string enemy3);
	virtual void SetFriend(string friend1, string friend2);
};
