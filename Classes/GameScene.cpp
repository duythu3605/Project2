#include "GameScene.h"
#include "Player.h"
#include "GameManager.h"
#include "Constant.h"
#include "ui/CocosGUI.h"
#include "Obstacles.h"
#include "Bomb.h"
#include"AudioEngine.h"

USING_NS_CC;
using namespace experimental;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	GameManager::resetGame();
	//////////////////////////////
	// 1. super init first
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Init game manager
	GameManager::setWorld(this);
	GameManager::start();

	// Init physics
	this->getPhysicsWorld()->setGravity(Vec2(0,-1000));
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

	// Init contact listeners
	this->initContactListener();

	// Init player
	this->player = GameManager::getPlayer() ? GameManager::getPlayer() : new Player();
	GameManager::addEntity(player);
	GameManager::setPlayer(player);
	this->player->getSprite()->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5));
	this->player->getSprite()->setLocalZOrder(1);
	
	


	
	//// Camera
	this->initCameraUI();

	//// GUI
	this->initBackground();
	this->initPauseMenu();
	this->initPlayerInfoUI();
	this->initYard();

	//// Mark
	this->initMarkUI();

	//Test audio 

	
	

	scheduleUpdate();
	return true;
}


Vec2 GameScene::getPositionP() {
	return this->position;
}

void GameScene::update(float dt) {
	
	
	PrePosition();
	PreRotation();
	this->updatePlayerInfo();
	this->Time_req();
	GameScene::setMark(std::to_string((int)GameScene::getTime_req()));
	this->textMark->setString(GameScene::getMark());
	/*GameManager::getInstance()->setMark(GameScene::getTime_req());*/
	GameManager::update(dt);
}
/// position player in scene
void GameScene::PrePosition() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = visibleSize.width;
	float y = visibleSize.height;

	Vec2 prePosition = this->player->getSprite()->getPosition();
	if (prePosition.x > x - 50) {
		Vec2 newPosition = Vec2(x - 50, prePosition.y);
		this->player->getSprite()->setPosition(newPosition);
	}
	else if (prePosition.x < 50) {
		Vec2 newPosition = Vec2(50, prePosition.y);
		this->player->getSprite()->setPosition(newPosition);
	}
}

// rotation player in Scene 
void GameScene::PreRotation() {
	float preRotate = this->player->getSprite()->getRotation();
	if (preRotate > 0)
	{
		this->player->getSprite()->setRotation(0);
	}
	else if (preRotate < 0)
	{
		this->player->getSprite()->setRotation(0);
	}
}

void GameScene::initContactListener() {
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}
bool GameScene::onContactBegin(PhysicsContact& contact) {
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB) {
		
		Obstacles* entityA = GameManager::findObstacles((Sprite*)nodeA);
		Entity* entityB = GameManager::findEntity((Sprite*)nodeB);
		int sound_blood;

		if (instanceof<Obstacles>(entityA) && instanceof<Entity>(entityB)) {
			float damageA = entityA->getDamage();
			float damageB = entityB->getDamage();
			entityA->takeDamage(damageB);
			entityB->takeDamage(damageA);
			/*sound_blood = AudioEngine::play2d("Audio/background.mp3");*/
		}
		else if (nodeA->getTag() == (int)ContactType::Heart) {
			float heartA = entityA->getDamage();
			float heartB = entityB->getDamage();
			//entityB->takeheart();
		}
		//AudioEngine::stop(sound_blood);
		else if (nodeA->getTag() == (int)ContactType::Sword || 
			nodeA->getTag() == (int)ContactType::Bomb || 
			nodeA->getTag() == (int)ContactType::Rock ||
			nodeA->getTag() == (int)ContactType::SawBlade)
		{
			GameManager::destroyObstacles(entityA);
		}

		
		
	}

	return true;
}

void GameScene::onContactSeparate(PhysicsContact& contact) {
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	
}


void GameScene::initPlayerInfoUI() {
	this->playerInfo = Node::create();
	playerInfo->setAnchorPoint(Vec2(0, 0.5));

	addChild(playerInfo);
	playerInfo->setPosition(Vec2(50, 50) - GameManager::getVisibleSize() / 2);
	
	
}

void GameScene::updatePlayerInfo() {
	
}

void GameScene::initYard(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto frontback = Sprite::create("Yard/yard1.png");
	frontback->setContentSize(Size(visibleSize.width, visibleSize.height*0.2));
	frontback->setAnchorPoint(Vec2(0, 0));

	//land body
	
	
	auto landBody1 = PhysicsBody::createBox(frontback->getContentSize());
	landBody1->setDynamic(false);
	frontback->addComponent(landBody1);
	frontback->getPhysicsBody()->setCategoryBitmask(YARD_CONTACT_TEST_BITMASK);
	frontback->getPhysicsBody()->setCollisionBitmask(YARD_CATEGORY_BITMASK);
	frontback->getPhysicsBody()->setContactTestBitmask(YARD_COLLISION_BITMASK);
	
	addChild(frontback);
}
void GameScene::initPauseMenu() {
	ui::Button* btnPause = ui::Button::create("Button/btnPauseNormal.png", "Button/btnPauseSelected.png", "Button/btnPauseNormal.png");
	btnPause->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			log("Pressed");
			scheduleOnce([](float dt) {
				GameManager::resume();
				}, 5, "resumeGame");
			GameManager::pause();
			break;
		default:
			break;
		}
		});

	float factor = 30; 
	float xscale = factor / btnPause->getContentSize().width;
	float yscale = factor / btnPause->getContentSize().height;
	btnPause->setScale(xscale, yscale);
	btnPause->setPosition(Vec2(50, GameManager::getVisibleSize().height - 50) - GameManager::getVisibleSize() / 2);
	addChild(btnPause);
	btnPause->setCameraMask((unsigned int)this->cameraUI->getCameraFlag());

}
void GameScene::Time_req() {
	if (GameManager::isPause == false) {
		this->time_req += cocos2d::Director::getInstance()->getDeltaTime();
		GameScene::setTime_req(this->time_req);
		float m = (int)GameScene::getTime_req();
		//CCLOG("%f", m);
		GameScene::level(m);
		
	}
}
void GameScene::setTime_req(float time) {
	this->time = time;
}
float GameScene::getTime_req() {
	return time;
}
void GameScene::setMark(string mark) {
	this->mark = mark;
}
string GameScene::getMark() {
	return mark;
}

void GameScene::initMarkUI() {
	this->textMark = TextFieldTTF::create("0", "fonts/arial.ttf", 30);
	float factor = 30; 
	float xscale = factor / this->textMark->getContentSize().width;
	float yscale = factor / this->textMark->getContentSize().height;
	this->textMark->setScale(xscale, yscale);
	this->textMark->setPosition(Vec2(900, GameManager::getVisibleSize().height - 50) - GameManager::getVisibleSize() / 2);
	addChild(this->textMark);
	this->textMark->setCameraMask((unsigned int)this->cameraUI->getCameraFlag());
}

void GameScene::initCameraUI() {
	this->cameraUI = Camera::create();
	this->cameraUI->setCameraFlag(CameraFlag::USER1);
	addChild(this->cameraUI);

	Vec3 eyePosOld = this->cameraUI->getPosition3D();
	this->cameraUI->setPosition3D(Vec3(0, 0, eyePosOld.z));
	this->cameraUI->lookAt(Vec3(0, 0, 0));
}
void GameScene::initBackground() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto windowLayer = Sprite::create("BackGround/BackGround.png");
	windowLayer->setContentSize(GameManager::getVisibleSize());
	windowLayer->setAnchorPoint(Vec2(0, 0));

	addChild(windowLayer);	
}
void GameScene::level(float time) {
	
	if (time >= 10 && time<=20) {
		CCLOG("tang toc do list size: %d", GameManager::obstacles.size());
		for (Obstacles *ob : GameManager::obstacles) {
			if (ob != NULL) {
				log("ob: %s", ob->getSprite()->getName().c_str());
				ob->setSpeed(200);
			}
		}
	}
	else if (time > 20 && time < 40) {
		CCLOG("tang toc do list size: %d", GameManager::obstacles.size());
		for (Obstacles *ob : GameManager::obstacles) {
			if (ob != NULL) {
				log("ob: %s", ob->getSprite()->getName().c_str());
				ob->setSpeed(300);
			}
		}
	}
	else if (time > 40 && time < 60) {
		CCLOG("tang toc do list size: %d", GameManager::obstacles.size());
		for (Obstacles *ob : GameManager::obstacles) {
			if (ob != NULL) {
				log("ob: %s", ob->getSprite()->getName().c_str());
				ob->setSpeed(400);
			}
		}
	}
	else if (time > 60 && time < 80) {
		CCLOG("tang toc do list size: %d", GameManager::obstacles.size());
		for (Obstacles *ob : GameManager::obstacles) {
			if (ob != NULL) {
				log("ob: %s", ob->getSprite()->getName().c_str());
				ob->setSpeed(500);
			}
		}
	}
	else if (time > 80 && time < 100) {
		CCLOG("tang toc do list size: %d", GameManager::obstacles.size());
		for (Obstacles *ob : GameManager::obstacles) {
			if (ob != NULL) {
				log("ob: %s", ob->getSprite()->getName().c_str());
				ob->setSpeed(600);
			}
		}
	}
}
