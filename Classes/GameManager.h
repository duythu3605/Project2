#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "Constant.h"
#include <vector>
#include "Obstacles.h"
#include "Player.h"

USING_NS_CC;

static class GameManager
{
private:
	static Scene* world;
	static std::vector<Obstacles*> enemies;
	static Player* player;
	static std::vector<Obstacles*> obstacles;
	static bool isPause;

	static void pauseGame();
	static void resumeGame();
public:
	GameManager();
	~GameManager();

	static void setWorld(Scene* world);
	static Scene* getWorld();
	static Size getVisibleSize();
	static Vec2 getVisibleOrigin();
	static Player* getPlayer();
	static void setPlayer(Player* player);
	static void addObstacles(Obstacles* entity);
	static Obstacles* findObstacles(Sprite* sprite);
	static void destroyObstacles(Obstacles* entity);

	static void spawnEnemies();
	static void start();
	static void update(float dt);
	static void end();
	static void pause();
	static void resume();
	static void nextStage();
};

#endif // __GAME_MANAGER_H__
