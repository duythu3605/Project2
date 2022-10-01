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
	static	GameScene*  mark;
	
	

	static void pauseGame();
	static void resumeGame();

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
	
	static void setMark(GameScene* mark);
	static GameScene* getMark();
	

	//static void destroyEnity(Entity* entity);

	static void spawnEnemies();
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
