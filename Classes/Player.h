#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Entity.h"


USING_NS_CC;

class Player : public Entity
{
private:
	
	int heart;

	void initEventListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	float jumpFoc;
	
public:
	Player();
	~Player();
	void init();
	void update(float dt);
	void takeDamage(float damage);
	void takeHeart(float heart);
	int getHeart();
	void setHeart(int heart);
	void die();
	void Jump();
};

#endif // __PLAYER_H__
