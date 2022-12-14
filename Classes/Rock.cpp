#include "Rock.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

Rock::Rock() : Obstacles("Obstacles/stone2.png") {
	this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
	this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	

	this->sprite->setTag((int)ContactType::Rock);
}

Rock::~Rock() {

}

void Rock::init()
{
	this->setSpeed(100);
	this->setDirection(Vec2::ZERO);
	this->damage = 300;
	this->maxHP = 10;
	this->hp = 10;
	

	Player* player = GameManager::getPlayer();
	auto position_player = player->getSprite()->getPosition();
	auto position_rock = this->sprite->getPosition();
	if (position_rock.y > position_player.y) {
		Vec2 a = player->getSprite()->getPosition() - this->sprite->getPosition() - Vec2(0, 200);
		float s = sqrt(((a.x)*(a.x) + (a.y)*(a.y)));
		auto move = MoveBy::create((int)(s / this->getSpeed()), player->getSprite()->getPosition() - this->sprite->getPosition() - Vec2(0, 500));
		this->sprite->runAction(move);
	}
	/*auto direct = player->getSprite()->getPosition() - this->sprite->getPosition();
	direct.normalize();
	this->setDirection(direct);*/
	
}

void Rock::update(float dt) {
	/*Player* player = GameManager::getPlayer();*/
	/*auto direct = player->getSprite()->getPosition() - this->sprite->getPosition();
	direct.normalize();
	this->setDirection(direct);*/
}
