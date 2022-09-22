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
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// Init contact listeners
	this->initContactListener();

	// Init player
	this->player = GameManager::getPlayer() ? GameManager::getPlayer() : new Player();
	this->player->getSprite()->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 7.1));
	this->player->getSprite()->setLocalZOrder(1);
	this->setPositionP(this->player->getSprite()->getPosition());
	GameManager::addObstacles(player);
	GameManager::setPlayer(player);

	//// Camera
	this->initCameraUI();

	//// GUI
	//this->initBackground();
	//this->initPauseMenu();
	this->initPlayerInfoUI();
	this->initYard();

	scheduleUpdate();
	return true;
}
void GameScene::setPositionP(Vec2 position) {
	this->position = position;
	
}

Vec2 GameScene::getPositionP() {
	return this->position;
}

void GameScene::update(float dt) {
	
	GameManager::update(dt);
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
		if (nodeA->getTag() == (int)ContactType::Sword)
		{
			nodeA->removeFromParentAndCleanup(true);
		}

		Obstacles* entityA = GameManager::findObstacles((Sprite*)nodeA);
		Obstacles* entityB = GameManager::findObstacles((Sprite*)nodeB);

		if (instanceof<Obstacles>(entityA) && instanceof<Obstacles>(entityB)) {
			float damageA = entityA->getDamage();
			float damageB = entityB->getDamage();
			entityA->takeDamage(damageB);
			entityB->takeDamage(damageA);
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
	
	playerInfo->setCameraMask((unsigned short)this->cameraUI->getCameraFlag());
}

void GameScene::updatePlayerInfo() {
	
}

void GameScene::followPlayer() {
	auto camera = getDefaultCamera();
	auto targetPos = player->getSprite()->getPosition();
	auto visibleSize = GameManager::getVisibleSize();
	targetPos.x = clampf(targetPos.x, visibleSize.width / 2 - (BOUNDING_BOX.width - visibleSize.width) / 2,
		visibleSize.width / 2 + (BOUNDING_BOX.width - visibleSize.width) / 2);
	targetPos.y = clampf(targetPos.y, visibleSize.height / 2 - (BOUNDING_BOX.height - visibleSize.height) / 2,
		visibleSize.height / 2 + (BOUNDING_BOX.height - visibleSize.height) / 2);
	auto curPos = camera->getPosition();
	curPos = curPos.lerp(targetPos, 0.1);
	camera->setPosition(curPos);
}

void GameScene::initCameraUI() {
	this->cameraUI = Camera::create();
	this->cameraUI->setCameraFlag(CameraFlag::USER1);
	addChild(this->cameraUI);

	Vec3 eyePosOld = this->cameraUI->getPosition3D();
	this->cameraUI->setPosition3D(Vec3(0, 0, eyePosOld.z));
	this->cameraUI->lookAt(Vec3(0, 0, 0));
}
void GameScene::initYard(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto frontback = Sprite::create("Yard/yard.png");
	frontback->setContentSize(Size(visibleSize.width, visibleSize.height* 0.1));
	frontback->setAnchorPoint(Vec2(0, 0));

	//land body
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	auto landBody1 = PhysicsBody::createBox(frontback->getContentSize());
	landBody1->setDynamic(false);
	frontback->addComponent(landBody1);
	frontback->getPhysicsBody()->setCategoryBitmask(YARD_CONTACT_TEST_BITMASK);
	frontback->getPhysicsBody()->setCollisionBitmask(YARD_CATEGORY_BITMASK);
	frontback->getPhysicsBody()->setContactTestBitmask(YARD_COLLISION_BITMASK);
	//frontback->setTag((int)ContactType::Yard);
	addChild(frontback);
}

//void GameScene::initBackground() {
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//	/*auto boundingBoxBorderLayer = LayerColor::create(Color4B(10, 10, 100, 255));
//	boundingBoxBorderLayer->setContentSize(BOUNDING_BOX);
//	boundingBoxBorderLayer->setPosition((boundingBoxBorderLayer->getContentSize() - GameManager::getVisibleSize()) / 2 * -1);
//	addChild(boundingBoxBorderLayer);*/
//
//	/*auto boundingBoxInnerLayer = LayerColor::create(Color4B(10, 100, 10, 255));
//	boundingBoxInnerLayer->setContentSize(BOUNDING_BOX - Size(20, 20));
//	boundingBoxInnerLayer->setPosition((boundingBoxInnerLayer->getContentSize() - GameManager::getVisibleSize()) / 2 * -1);
//	addChild(boundingBoxInnerLayer);*/
//
//
//
//	auto windowLayer = Sprite::create("galaxy3.jpg");
//	//windowLayer->setContentSize(GameManager::getVisibleSize());
//	windowLayer->setContentSize(Size(800, 800));
//	windowLayer->setPosition(visibleSize*0.5);
//
//	addChild(windowLayer);
//
//	
//}
