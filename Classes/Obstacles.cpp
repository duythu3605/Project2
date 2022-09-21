#include "Obstacles.h"
#include "Constant.h"
#include "GameManager.h"

USING_NS_CC;

Obstacles::Obstacles() {

}

Obstacles::Obstacles(const string& file) {
	this->sprite = Sprite::create(file);

	this->body = PhysicsBody::createBox(this->sprite->getContentSize());
	this->body->setDynamic(false);
	this->sprite->addComponent(body);
	this->sprite->setTag((int)ContactType::None);

	this->init();
}

Obstacles::~Obstacles() {

}

void Obstacles::init()
{
	this->speed = 0;
	this->direction = Vec2::ZERO;
	this->maxHP = 0;
	this->hp = 0;
	this->damage = 0;
}

void Obstacles::update(float dt) {
}

void Obstacles::setSpeed(float speed) {
	this->speed = speed;
	this->body->setVelocity(direction * speed);
}

float Obstacles::getSpeed() {
	return this->speed;
}

float Obstacles::getHP() {
	return this->hp;
}

void Obstacles::setHP(float hp) {
	this->hp = hp;
}

void Obstacles::setDirection(Vec2 direction) {
	this->direction = direction;
	this->body->setVelocity(direction * speed);
}

Vec2 Obstacles::getDirection() {
	return this->direction;
}

Sprite* Obstacles::getSprite() {
	return this->sprite;
}

void Obstacles::destroy() {
	this->sprite->removeFromParentAndCleanup(true);
}



float Obstacles::getDamage() {
	return this->damage;
}

void Obstacles::setDamage(float damage) {
	this->damage = damage;
}

void Obstacles::takeDamage(float damage) {
	this->hp -= damage;

	if (this->hp <= 0) {
		this->hp = 0;
		//this->sprite->setVisible(false);
		GameManager::destroyObstacles(this);
	}
}

void Obstacles::setMaxHP(float maxHP) {
	this->maxHP = maxHP;
}

float Obstacles::getMaxHP() {
	return this->maxHP;
}


void Obstacles::pause() {
	this->body->setVelocity(Vec2::ZERO);
	this->sprite->pause();
}

void Obstacles::resume() {
	this->body->setVelocity(this->speed * this->direction);
	this->sprite->resume();
}

