#include "Player.h"
#include "GameManager.h"

USING_NS_CC;

Player::Player() : Entity("Player/player.png") {
	this->sprite->removeComponent(this->body);
	this->body = PhysicsBody::createBox(this->sprite->getContentSize() , PhysicsMaterial(1.0f, 0, 0));
	this->body->setDynamic(true);
	this->sprite->addComponent(body);
	this->body->setContactTestBitmask(PLAYER_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	this->sprite->setScale(0.7f);
	
	
	this->init();

}

Player::~Player() {
	
}

void Player::init()
{

	this->damage = 100;
	this->heart = 2;
	this->maxHeart = 2;
	this->setSpeed(300);
	this->setMaxHP(1);
	this->setHP(1);
	this->jumpFoc = 600;
	this->initEventListener();
	
}

void Player::takeDamage(float damage) {
	this->hp -= damage;
	if (this->hp <= 0) {
		if (this->heart > 0) {
			this->heart--;
			this->hp = this->maxHP;
		}
		else {
			this->hp = 0;
		}
	}
}
void Player::takeHeart(float heart) {
	this->heart += heart;
}

void Player::Jump() {
	this->body->setVelocity(Vec2(0, this->jumpFoc));
}
int Player::getHeart() {
	return this->heart;
}

void Player::setHeart(int heart) {
	this->heart = heart;
}

void Player::die() {
	auto node = Node::create();
	node->scheduleOnce([&](float dt) {
		GameManager::end();
		}, 1, "EndGame");
	GameManager::getWorld()->addChild(node);

	this->pause();
}

void Player::update(float dt) {
	auto newDirection = direction;
	if (this->hp == 0) {
		this->die();
	}	

	if (this->sprite->getPositionY() > GameManager::getVisibleSize().height / 5.5) {
		this->body->setGravityEnable(true);
	}
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
		newDirection.normalize();
		setDirection(newDirection);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		newDirection.x = 1;
		newDirection.normalize();
		setDirection(newDirection);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		this->Jump();
		this->body->setGravityEnable(false);
		break;
	default:
		break;
	}
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	auto newDirection = direction;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		newDirection.x = 0;
		newDirection.normalize();
		setDirection(newDirection);
		
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:	
		this->body->setGravityEnable(true);
		break;
	default:
		break;
	}
	
	
}





