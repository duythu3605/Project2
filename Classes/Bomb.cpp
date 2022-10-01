#include "Bomb.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

Bomb::Bomb() : Obstacles("Obstacles/bomb.png") {
	this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	this->sprite->setTag((int)ContactType::Bomb);
	this->sprite->setName("Bomb");
}

Bomb::~Bomb() {

}

void Bomb::init()
{
	this->setSpeed(100);
	this->setDirection(Vec2::ZERO);
	this->damage = 300;
	this->maxHP = 10;
	this->hp = 10;
	

	Player* player = GameManager::getPlayer();
	auto move = MoveBy::create(7-((int)this->getSpeed()/100), player->getSprite()->getPosition() - this->sprite->getPosition() - Vec2(0,500));
	auto move_ease_in = EaseBackIn::create(move->clone());
	auto seq1 = cocos2d::Sequence::create(move_ease_in, nullptr);
	this->sprite->runAction(seq1);
	
	
}

void Bomb::update(float dt) {
	/*Player* player = GameManager::getPlayer();*/
	/*auto direct = player->getSprite()->getPosition() - this->sprite->getPosition();
	direct.normalize();
	this->setDirection(direct);*/
}
