#ifndef __SWORD_H__
#define __SWORD_H__

#include "cocos2d.h"
#include "Obstacles.h"

USING_NS_CC;

class Sword : public Obstacles
{
private:
public:
	Sword();
	~Sword();
	void init();
	void update(float dt);
};

#endif // __SWORD_H__
