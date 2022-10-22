#ifndef __HEART_H__
#define __HEART_H__

#include "cocos2d.h"
#include "Obstacles.h"

USING_NS_CC;

class Heart : public Obstacles
{
private:
public:
	Heart();
	~Heart();
	void init();
	void onDestroy();
	void update(float dt);
	
};

#endif // __HEART_H__
