#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"
using namespace cocos2d;
enum DirectState
{
	UP = 0, DOWN
};

class Bullet
{
public :
	Bullet(bool isMultiAttack, float lifeTime, 
		int magic, int attackPoint,
		const CCRect& collisionRect, DirectState dir);
	void update(float dt);
	bool isMultiAttack();
	bool isDie();
	void setDie();
	int getAP();

	CCRect mCollisionRect;

public :
	bool mIsMultiAttack;
	float mLifeTime;
	int m_magci;
	int mAttackPoint;
	DirectState mDirection;
};

#endif