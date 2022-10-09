#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Entity
{
private:
protected:
	Sprite* sprite;
	float speed;
	Vec2 direction;
	PhysicsBody* body;

	float maxHP;
	float hp;
	float damage;
	float heart;
	float maxHeart;
	

public:
	enum Enemies {
		
	};

	Entity();
	Entity(const string& file);
	~Entity();
	virtual void init();
	virtual void update(float dt);
	virtual void destroy();
	void setSpeed(float speed);
	float getSpeed();
	void setDirection(Vec2 direction);
	Vec2 getDirection();
	Sprite* getSprite();
	void setMaxHP(float hp);
	float getMaxHP();
	void setHP(float hp);
	float getHP();
	float getHeart();
	void setHeart(float heart);
	float getMaxheart();
	void setMaxheart(float heart);
	void setDamage(float damage);
	float getDamage();
	virtual void takeDamage(float damage);
	virtual void takeHeart_req(float heart);
	void pause();
	void resume();
};

#endif // __ENTITY_H__
