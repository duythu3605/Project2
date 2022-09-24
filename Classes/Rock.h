#ifndef __ROCK_H__
#define __ROCK_H__

#include "cocos2d.h"
#include "Obstacles.h"

USING_NS_CC;

class Rock : public Obstacles
{
private:
public:
	Rock();
	~Rock();
	void init();
	void update(float dt);
};

#endif // __ROCK_H__
