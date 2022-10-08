#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "Constant.h"
#include <vector>
#include "Obstacles.h"
#include "Entity.h"
#include "Player.h"
#include "GameScene.h"

USING_NS_CC;

static class GameManager
{
public:
	static Scene* world;
	static std::vector<Entity*> entities;
	static std::vector<Obstacles*> enemies;
	static Player* player;
	static std::vector<Obstacles*> obstacles;
	static bool isPause;
	//static	float  mark;
	static GameManager* getInstance();
	/*static int id_sword_sound;
	static int id_rock_sound;
	static int id_sawblade_sound;
	static int id_bomb_sound;*/
	
	

	static void pauseGame();
	static void resumeGame();
	static void resetGame();

	GameManager();
	~GameManager();

	static void setWorld(Scene* world);
	static Scene* getWorld();
	static Size getVisibleSize();
	static Vec2 getVisibleOrigin();
	static Player* getPlayer();
	static void setPlayer(Player* player);
	static void addEntity(Entity* entity);
	static void addObstacles(Obstacles* obstacle);
	static Obstacles* findObstacles(Sprite* sprite);
	static Entity* findEntity(Sprite* sprite);
	static void destroyObstacles(Obstacles* entity);
	
	/*void setMark(float mark);
	float  getMark();*/
	

	//static void destroyEnity(Entity* entity);

	static void spawnSwords();
	static void spawnRock();
	static void spawnBomb();
	static void spawnSawBlade();
	static void start();
	static void update(float dt);
	static void end();
	static void pause();
	static void resume();
	
	

};

#endif // __GAME_MANAGER_H__
