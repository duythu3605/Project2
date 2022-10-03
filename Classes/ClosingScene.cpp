#include "ClosingScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include"GameManager.h"

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

	auto label_gameover = Label::createWithSystemFont("Game Over", "Arial", 30);
	addChild(label_gameover);
	label_gameover->setPosition(visibleSize.width/2 , visibleSize.height/1.2);

	auto label_total = Label::createWithSystemFont("Total", "Arial", 20);
	addChild(label_total);
	label_total->setPosition(visibleSize.width / 2, visibleSize.height / 1.4);

	// getvalue mark from GameScene (use GameManager)
	/*GameManager::getInstance()->getMark();
	std::string v = std::to_string(GameManager::getInstance()->getMark());*/

	//GameScene::setMark(std::to_string((int)GameScene::getTime_req()));
	auto label_totalmark = Label::createWithSystemFont("0" , "Arial", 20);
	addChild(label_totalmark);
	label_totalmark->setPosition(visibleSize.width / 2, visibleSize.height / 1.5);
	Vector<MenuItem*> menuItems = {
		MenuItemLabel::create(Label::createWithSystemFont("Play Again", "Arial", 20)  , [=](Ref* sender) {
		/*auto gameScene = GameScene::create();
			Director::getInstance()->replaceScene(gameScene);*/
			
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

