#ifndef __BOMB_H__
#define __BOMB_H__

#include "cocos2d.h"
#include "Obstacles.h"

USING_NS_CC;

class Bomb : public Obstacles
{
private:
public:
	Bomb();
	~Bomb();
	void init();
	void update(float dt);
};

#endif // __BOMB_H__
