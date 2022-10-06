#ifndef __CLOSING_SCENE_H__
#define __CLOSING_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class ClosingScene : public Scene
{
public:
	Scene* createScene();

	virtual bool init();

	void menuCloseCallBack(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ClosingScene);
};

#endif // __CLOSING_SCENE_H__
