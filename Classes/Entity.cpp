#include "Entity.h"
#include "Constant.h"
#include "GameManager.h"

USING_NS_CC;

Entity::Entity() {

}

Entity::Entity(const string& file) {
	this->sprite = Sprite::create(file);

	this->body = PhysicsBody::createBox(this->sprite->getContentSize());
	this->body->setDynamic(false);
	this->sprite->addComponent(body);
	this->sprite->setTag((int)ContactType::NoneP);

	this->init();
}

Entity::~Entity() {

}

void Entity::init()
{
	this->speed = 0;
	this->direction = Vec2::ZERO;
	this->maxHP = 0;
	this->hp = 0;
	this->damage = 0;
	this->heart = 0;
	this->maxHeart = 0;
}

void Entity::update(float dt) {
}

void Entity::setSpeed(float speed) {
	this->speed = speed;
	this->body->setVelocity(direction * speed);
}

float Entity::getSpeed() {
	return this->speed;
}

float Entity::getHP() {
	return this->hp;
}

void Entity::setHP(float hp) {
	this->hp = hp;
}

float Entity::getHeart() {
	return this->heart;
}
void Entity::setHeart(float heart) {
	this->heart = heart;
}

void Entity::setDirection(Vec2 direction) {
	this->direction = direction;
	this->body->setVelocity(direction * speed);
}

Vec2 Entity::getDirection() {
	return this->direction;
}

Sprite* Entity::getSprite() {
	return this->sprite;
}

void Entity::destroy() {
	//this->sprite->removeFromParentAndCleanup(true);
}



float Entity::getDamage() {
	return this->damage;
}

void Entity::setDamage(float damage) {
	this->damage = damage;
}

void Entity::takeDamage(float damage) {
	this->hp -= damage;

	if (this->hp <= 0) {
		this->hp = 0;
	}
}
void Entity::takeHeart_req(float heart) {
	this->heart += heart;
}

void Entity::setMaxHP(float maxHP) {
	this->maxHP = maxHP;
}

float Entity::getMaxHP() {
	return this->maxHP;
}
void Entity::setMaxheart(float maxHeart) {
	this->maxHeart = maxHeart;
}
float Entity::getMaxheart() {
	return this->maxHeart;
}

void Entity::pause() {
	this->body->setVelocity(Vec2::ZERO);
	this->sprite->pause();
}

void Entity::resume() {
	this->body->setVelocity(this->speed * this->direction);
	this->sprite->resume();
}

