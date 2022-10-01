#ifndef __SAWBLADE_H__
#define __SAWBLADE_H__

#include "cocos2d.h"
#include "Obstacles.h"

USING_NS_CC;

class SawBlade : public Obstacles
{
private:
public:
	SawBlade();
	~SawBlade();
	void init();
	void update(float dt);
};

#endif // __SAWBLADE_H__
