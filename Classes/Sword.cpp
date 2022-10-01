#include "Sword.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

Sword::Sword() : Obstacles("Obstacles/sword.png") {
	this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	

	this->sprite->setTag((int)ContactType::Sword);
}

Sword::~Sword() {

}

void Sword::init()
{
	this->setSpeed(100);
	this->setDirection(Vec2::ZERO);
	this->damage = 300;
	this->maxHP = 10;
	this->hp = 10;

	Player* player = GameManager::getPlayer();
	auto direct = player->getSprite()->getPosition() - this->sprite->getPosition();
	direct.normalize();
	this->setDirection(direct);
	
}

void Sword::update(float dt) {
	/*Player* player = GameManager::getPlayer();*/
	/*auto direct = player->getSprite()->getPosition() - this->sprite->getPosition();
	direct.normalize();
	this->setDirection(direct);*/
}
