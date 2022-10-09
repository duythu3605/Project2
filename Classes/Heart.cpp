#include "Heart.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

Heart::Heart() : Obstacles("Obstacles/heart.png") {
	this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	this->sprite->setTag((int)ContactType::Heart);
	this->sprite->setScale(0.2, 0.2);
	
}

Heart::~Heart() {

}

void Heart::init()
{
	this->setSpeed(300);
	this->setDirection(Vec2::ZERO);
	this->heart = 1;
	this->maxHP = 10;
	this->hp = 10;
	

	Player* player = GameManager::getPlayer();
	/*auto move = MoveBy::create(7-((int)this->getSpeed()/100), player->getSprite()->getPosition() - this->sprite->getPosition() - Vec2(0,500));*/
	
	auto move = MoveBy::create(7, player->getSprite()->getPosition() - this->sprite->getPosition() - Vec2(0, 500));
	
	this->sprite->runAction(move);
	
	
}

void Heart::update(float dt) {
	/*Player* player = GameManager::getPlayer();*/
	/*auto direct = player->getSprite()->getPosition() - this->sprite->getPosition();
	direct.normalize();
	this->setDirection(direct);*/
}
