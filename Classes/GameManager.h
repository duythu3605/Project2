#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "Constant.h"
#include <vector>
#include "Obstacles.h"
#include "Entity.h"
#include "Player.h"

USING_NS_CC;

static class GameManager
{
public:
	static Scene* world;
	static Scene* startscene;
	static Scene* gamescene;
	static std::vector<Entity*> entities;
	static std::vector<Obstacles*> enemies;
	static Player* player;
	static std::vector<Obstacles*> obstacles;
	static bool isPause;
	static float mark;

	static void pauseGame();
	static void resumeGame();

	GameManager();
	~GameManager();

	static void setWorld(Scene* world);
	static Scene* getWorld();
	static void setStart(Scene* start);
	static Scene* getStart();
	static Size getVisibleSize();
	static Vec2 getVisibleOrigin();
	static Player* getPlayer();
	static void setPlayer(Player* player);
	static void addEntity(Entity* entity);
	static void addObstacles(Obstacles* obstacle);
	static Obstacles* findObstacles(Sprite* sprite);
	static Entity* findEntity(Sprite* sprite);
	static void destroyObstacles(Obstacles* entity);
	static void setMark(float time);
	static float getMark();

	//static void destroyEnity(Entity* entity);

	static void spawnEnemies();
	static void start();
	static void update(float dt);
	static void end();
	static void pause();
	static void resume();
	static void nextStage();
	static void pushScene(Scene* gameScene);
	static void popScene();

};

#endif // __GAME_MANAGER_H__
