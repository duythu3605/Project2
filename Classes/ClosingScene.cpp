#include "ClosingScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* ClosingScene::createScene()
{
	return ClosingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ClosingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithSystemFont("Game Over", "Arial", 30);
	addChild(label);
	label->setPosition(visibleSize / 2);

	Vector<MenuItem*> menuItems = {
		MenuItemLabel::create(Label::createWithSystemFont("Play Again", "Arial", 20)  , [=](Ref* sender) {
		auto gameScene = GameScene::create();
			Director::getInstance()->replaceScene(gameScene);
			
		}),
		MenuItemLabel::create(Label::createWithSystemFont("Quit", "Arial", 20)  , [=](Ref* sender) {
			Director::getInstance()->end();
		}),
	};

	auto menu = Menu::createWithArray(menuItems);
	addChild(menu);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.8));

	return true;
}

