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

	// back ground
	auto windowLayer = Sprite::create("BackGround/BackGround.png");
	windowLayer->setContentSize(GameManager::getVisibleSize());
	windowLayer->setAnchorPoint(Vec2(0, 0));
	addChild(windowLayer);
	// Label
	auto pic_gameover = Sprite::create("Button/youdie.png");	
	addChild(pic_gameover);
	pic_gameover->setPosition(visibleSize.width/2 , visibleSize.height/1.2);

	auto pic_score = Sprite::create("Button/score.png");
	pic_score->setScale(0.7f);
	addChild(pic_score);
	pic_score->setPosition(visibleSize.width / 2, visibleSize.height / 1.4);

	// getvalue mark from GameScene 
	
	string n = std::to_string((int)GameManager::getMark());
	auto label_totalmark = Label::createWithSystemFont(n , "Arial", 40);
	label_totalmark->setColor(Color3B::BLACK);
	addChild(label_totalmark);
	label_totalmark->setPosition(visibleSize.width / 2, visibleSize.height / 1.65);


	/*Vector<MenuItem*> menuItems = {
		MenuItemLabel::create(Label::createWithSystemFont("Play Again", "Arial", 20)  ,CC_CALLBACK_1(ClosingScene::menuCloseCallBack,this)),
		MenuItemLabel::create(Label::createWithSystemFont("Quit", "Arial", 20)  , [=](Ref* sender) {
			Director::getInstance()->end();
		}),
	};*/

	Vector<MenuItem*> menuItems = {
		MenuItemImage::create("Button/btnplay.png","Button/btnplay_pressed.png",[&](Ref* sender) {
			auto gameScene = GameScene::create();
		Director::getInstance()->replaceScene(gameScene);
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
//
//void ClosingScene::menuCloseCallBack(Ref* pSender) {
//	auto gameScene = GameScene::create();
//	Director::getInstance()->replaceScene(gameScene);
//}

