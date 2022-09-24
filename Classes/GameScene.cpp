#include "GameScene.h"
#include "Player.h"
#include "GameManager.h"
#include "Constant.h"
#include "ui/CocosGUI.h"
#include "Obstacles.h"

USING_NS_CC;

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
	this->getPhysicsWorld()->setGravity(Vec2(0,-300));
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

	// Init contact listeners
	this->initContactListener();

	// Init player
	this->player = GameManager::getPlayer() ? GameManager::getPlayer() : new Player();
	this->player->getSprite()->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5));
	this->player->getSprite()->setLocalZOrder(1);
	
	GameManager::addEntity(player);
	GameManager::setPlayer(player);

	//// Camera
	this->initCameraUI();

	//// GUI
	this->initBackground();
	this->initPauseMenu();
	this->initPlayerInfoUI();
	this->initYard();

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

	
	GameManager::update(dt);
}

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
		/*nodeA->setColor(Color3B::BLACK);
		nodeB->setColor(Color3B::BLACK);*/
		Obstacles* entityA = GameManager::findObstacles((Sprite*)nodeA);
		Entity* entityB = GameManager::findEntity((Sprite*)nodeB);

		if (instanceof<Obstacles>(entityA) && instanceof<Entity>(entityB)) {
			float damageA = entityA->getDamage();
			float damageB = entityB->getDamage();
			entityA->takeDamage(damageB);
			entityB->takeDamage(damageA);
		}
		else if (nodeA->getTag() == (int)ContactType::Sword || nodeA->getTag() == (int)ContactType::Bomb || nodeA->getTag() == (int)ContactType::Rock)
		{
			nodeA->removeFromParentAndCleanup(true);
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

	auto frontback = Sprite::create("Yard/foot.png");
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
			GameManager::pause();
			scheduleOnce([](float dt) {
				GameManager::resume();
				}, 1, "resumeGame");
			break;
		default:
			break;
		}
		});

	float factor = 30; //GameManager::getVisibleSize().width / 16;
	float xscale = factor / btnPause->getContentSize().width;
	float yscale = factor / btnPause->getContentSize().height;
	btnPause->setScale(xscale, yscale);
	btnPause->setPosition(Vec2(50, GameManager::getVisibleSize().height - 50) - GameManager::getVisibleSize() / 2);
	addChild(btnPause);
	btnPause->setCameraMask((unsigned int)this->cameraUI->getCameraFlag());

	/*auto followPlayer = Follow::create(player->getSprite(), Rect(0,
		0, 1600, 1200));
	runAction(followPlayer);*/
}
//void GameScene::initMark() {
//	
//}
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
	/*auto boundingBoxBorderLayer = LayerColor::create(Color4B(10, 10, 100, 255));
	boundingBoxBorderLayer->setContentSize(BOUNDING_BOX);
	boundingBoxBorderLayer->setPosition((boundingBoxBorderLayer->getContentSize() - GameManager::getVisibleSize()) / 2 * -1);
	addChild(boundingBoxBorderLayer);*/

	/*auto boundingBoxInnerLayer = LayerColor::create(Color4B(10, 100, 10, 255));
	boundingBoxInnerLayer->setContentSize(BOUNDING_BOX - Size(20, 20));
	boundingBoxInnerLayer->setPosition((boundingBoxInnerLayer->getContentSize() - GameManager::getVisibleSize()) / 2 * -1);
	addChild(boundingBoxInnerLayer);*/



	auto windowLayer = Sprite::create("BackGround/BackGround.png");
	windowLayer->setContentSize(GameManager::getVisibleSize());
	//windowLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
	/*windowLayer->setPosition(visibleSize*0.5);*/
	windowLayer->setAnchorPoint(Vec2(0, 0));

	addChild(windowLayer);

	
}
