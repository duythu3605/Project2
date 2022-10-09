#ifndef __OBSTACLES_H__
#define __OBSTACLES_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Obstacles
{
private:
public:
	Sprite* sprite;
	float speed;
	Vec2 direction;
	PhysicsBody* body;
	Action* action_move;

	float maxHP;
	float hp;
	float damage;
	float heart;
	


	enum Enemies {
		Sword,
		Bomb,
		Rock,
		SawBlade,
		Heart,
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
	void setAction(Action action);
	Action* getAction();
	void setMaxHP(float hp);
	float getMaxHP();
	void setHP(float hp);
	float getHP();
	void setDamage(float damage);
	float getDamage();
	void setHeart(float heart);
	float getHeart();
	virtual void takeDamage(float damage);
	virtual void takeHeart(float heart);
	void pause();
	void resume();
};

#endif // __OBSTACLES_H__
