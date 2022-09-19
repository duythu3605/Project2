#ifndef __OBSTACLES_H__
#define __OBSTACLES_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Obstacles
{
private:
protected:
	Sprite* sprite;
	float speed;
	Vec2 direction;
	PhysicsBody* body;

	float damage;

public:
	enum Enemies {
		Sword,
	};

	Obstacles();
	Obstacles(const string& file);
	~Obstacles();
	virtual void init();
	virtual void update(float dt);
	virtual void destroy();
	void setSpeed(float speed);
	float getSpeed();
	void setDirection(Vec2 direction);
	Vec2 getDirection();
	Sprite* getSprite();
	void setDamage(float damage);
	float getDamage();
	void pause();
	void resume();
};

#endif // __OBSTACLES_H__
