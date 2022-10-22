#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "GameScene.h"
#include "GameManager.h"
#include"AudioManager.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Background
	auto windowLayer = Sprite::create("BackGround/BackGroundStart1.jpg");
	windowLayer->setContentSize(GameManager::getVisibleSize());
	windowLayer->setAnchorPoint(Vec2(0, 0));

	addChild(windowLayer);

	// music background
	AudioManager::set_idBG("Audio/background3.mp3", true);
	AudioManager::get_idBG();
	
	Vector<MenuItem*> menuItems = {
		MenuItemImage::create("Button/btnplay.png","Button/btnplay_pressed.png",[&](Ref* sender) {
			this->gameScene = GameScene::create();
			Director::getInstance()->replaceScene(this->gameScene);
			AudioManager::StopMusic(AudioManager::get_idBG());
		}),
		MenuItemImage::create("Button/btnvolume.png","Button/btnvolume_pressed.png",[&](Ref* sender) { 
			if(soundOn == true){
				AudioManager::PauseSound();
				soundOn = false;
			}
			else {
				AudioManager::ResumeSound();
				soundOn = true;
			}
				
			
		}),
		MenuItemImage::create("Button/btnquit.png","Button/btnquit_pressed.png",[&](Ref* sender) {
			Director::getInstance()->end();
			
		}),
	};

	auto menu = Menu::createWithArray(menuItems);
	addChild(menu);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	

	return true;
}

