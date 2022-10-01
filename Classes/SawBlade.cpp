#include "SawBlade.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

SawBlade::SawBlade() : Obstacles("Obstacles/sawblade.jpg") {
	this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	

	this->sprite->setTag((int)ContactType::SawBlade);
}

SawBlade::~SawBlade() {

}

void SawBlade::init()
{
	this->setSpeed(100);
	this->setDirection(Vec2::ZERO);
	this->damage = 300;
	this->maxHP = 10;
	this->hp = 10;
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Player* player = GameManager::getPlayer();
	auto position_player = player->getSprite()->getPosition();
	auto position_sawblade= this->sprite->getPosition();
	
	if (position_player.x > visibleSize.width / 2) {
		auto move_left = MoveBy::create(7 - ((int)this->getSpeed() / 100), Vec2(visibleSize.width, 0));
		this->sprite->runAction(move_left);
	}
	else {
		auto move_right = MoveBy::create(7 - ((int)this->getSpeed() / 100), Vec2(-visibleSize.width, 0));
		this->sprite->runAction(move_right);
	}
	
}

void SawBlade::update(float dt) {
	
}
