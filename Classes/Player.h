#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Obstacles.h"


USING_NS_CC;

class Player : public Obstacles
{
private:
	
	int heart;

	void initEventListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
public:
	Player();
	~Player();
	void init();
	void update(float dt);
	void takeDamage(float damage);
	int getHeart();
	void setHeart(int heart);
	void die();
	void levelUp();
};

#endif // __PLAYER_H__
