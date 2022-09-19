#include "Player.h"
#include "GameManager.h"

USING_NS_CC;

Player::Player() : Obstacles("Player/playertest.png") {
	this->body->setContactTestBitmask(PLAYER_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);

	this->init();
}

Player::~Player() {

}

void Player::init()
{

	this->damage = 100;
	this->heart = 1;

	this->setSpeed(300);

	this->initEventListener();
}




int Player::getHeart() {
	return this->heart;
}

void Player::setHeart(int heart) {
	this->heart = heart;
}

//void Player::die() {
//	auto node = Node::create();
//	node->scheduleOnce([&](float dt) {
//		GameManager::end();
//		}, 5, "EndGame");
//	GameManager::getWorld()->addChild(node);
//
//	this->pause();
//}

void Player::update(float dt) {
	/*if (this->heart <= 0) {
		this->die();
	}*/
}

void Player::initEventListener() {		
	// Init keyboard event listeners
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this->sprite);
}



void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	auto newDirection = direction;

	switch (keyCode) {	
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		newDirection.x = -1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		newDirection.x = 1;
		break;
	default:
		break;
	}

	newDirection.normalize();
	setDirection(newDirection);
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	auto newDirection = direction;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		newDirection.x = 0;
		break;
	default:
		break;
	}

	newDirection.normalize();
	setDirection(newDirection);
}



