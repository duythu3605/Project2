#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "cocos2d.h"

USING_NS_CC;

class Collidable {
public:
	virtual void takeDamage(float damage) {

	}

	virtual float getDamage() {
		return 0;
	}

};

enum class ContactType {
	None,
	NoneP,
	Obstacles,
	Player,
	Sword,
	Yard,
	Bomb,
	Rock,
	SawBlade,
	Heart,

	
};

// Player can collide with: Enemy, Enemy Bullet
const int PLAYER_CONTACT_TEST_BITMASK = 0x06; // 0110
const int PLAYER_CATEGORY_BITMASK = 0x09; // 1001
const int PLAYER_COLLISION_BITMASK = 0xFFFFFFFF;

// Obstaccles can collide with: Player
const int ENEMY_CONTACT_TEST_BITMASK = 0x09; // 1001
const int ENEMY_CATEGORY_BITMASK = 0x06; // 0110
const int ENEMY_COLLISION_BITMASK = 0xFFFFFFFF;

//Yard
const int YARD_CONTACT_TEST_BITMASK = 0x01; // 0001
const int YARD_CATEGORY_BITMASK = 0x07; // 0111
const int YARD_COLLISION_BITMASK = 0xFFFFFFFF;


// Bouding Box
const Size BOUNDING_BOX = Size(1200, 1200);

#endif // !__CONSTANT_H__