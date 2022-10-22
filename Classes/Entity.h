#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Entity 
{

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
	virtual void setSpeed(float speed);
	virtual float getSpeed();
	virtual void setDirection(Vec2 direction);
	virtual Vec2 getDirection();
	virtual Sprite* getSprite();
	virtual void setMaxHP(float hp);
	virtual float getMaxHP();
	virtual void setHP(float hp);
	virtual float getHP();
	virtual int getHeart();
	virtual void setHeart(float heart);
	virtual float getMaxheart();
	void setMaxheart(float heart);
	virtual void setDamage(float damage);
	virtual float getDamage();
	virtual void takeDamage(float damage);
	virtual void takeHeart_req(float heart);
	void pause();
	void resume();
};

#endif // __ENTITY_H__
