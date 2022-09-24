#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainMenuScene : public Scene
{
public:
	int backgroundMusic = -1;
	bool soundOn = true;
	Label *soundLabel;
	Scene* gameScene;
	

	static Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H__
