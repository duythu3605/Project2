#include "GameManager.h"
#include <cstdlib>
#include <ctime>
//#include <math.h>
#include "Sword.h"
#include "Bomb.h"
#include "Rock.h"
#include "SawBlade.h"
#include "MainMenuScene.h"
#include "ClosingScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameManager::world = NULL;
//Scene* GameManager::startscene = NULL;
	std::vector<Entity*> GameManager::entities;
	std::vector<Obstacles*> GameManager::enemies;
	std::vector<Obstacles*> GameManager::obstacles;
bool GameManager::isPause = false;

Player* GameManager::player = NULL;

GameManager::GameManager() {
}

GameManager::~GameManager() {

}
static  GameManager* getInstance()
{
	static GameManager *instance = new GameManager();
	return instance;
}

void GameManager::setWorld(Scene* world) {
	GameManager::world = world;
}

Scene* GameManager::getWorld() {
	return GameManager::world;
}

Size GameManager::getVisibleSize() {
	return Director::getInstance()->getVisibleSize();
}

Vec2 GameManager::getVisibleOrigin() {
	return Director::getInstance()->getVisibleOrigin();
}

void GameManager::setPlayer(Player* player) {
	GameManager::player = player;
}

Player* GameManager::getPlayer() {
	return player;
}


void GameManager::start() {
	srand(time(NULL));
// Schedule spawn enemies
	world->schedule([](float dt) {
		spawnEnemies();
		}, 2, "SpawnEnemies");
	
	world->schedule([](float dt) {
		spawnRock();
		}, 5, "spawnRock");
	world->schedule([](float dt) {
		spawnBomb();
		}, 3, "spawnBomb");
	world->schedule([](float dt) {
		spawnSawBlade();
		}, 3, "spawnSawBlade");
	
}

void GameManager::spawnEnemies() {
	int enemyMaxRand = 1;
	int enemyMinRand = 0;
	int enemyType = rand() % (enemyMaxRand - enemyMinRand + 1) + enemyMinRand;

	Vec2 position = Vec2 (random(100, 800),800);
	

	Obstacles* enemy = NULL;
	switch (enemyType) {
	case Obstacles::Sword:
		enemy = new Sword();
		break;
	default:
		enemy = new Sword();
		break;
	}

	enemy->getSprite()->setPosition(position);
	GameManager::world->addChild(enemy->getSprite());
	enemy->init();
	
	enemies.push_back(enemy);
	obstacles.push_back(enemy);
}
void GameManager::spawnRock() {
	int enemyMaxRand = 1;
	int enemyMinRand = 0;
	int enemyType = rand() % (enemyMaxRand - enemyMinRand + 1) + enemyMinRand;
	Player* player = GameManager::getPlayer();
	auto position_player = player->getSprite()->getPosition();
	Vec2 position = Vec2(position_player.x, 800);


	Obstacles* enemy = NULL;
	switch (enemyType) {
	
	case Obstacles::Rock:
		enemy = new Rock();
		break;
	default:
		enemy = new Rock();
		break;
	}

	enemy->getSprite()->setPosition(position);
	GameManager::world->addChild(enemy->getSprite());
	enemy->init();

	enemies.push_back(enemy);
	obstacles.push_back(enemy);
}
void GameManager::spawnBomb() {
	int enemyMaxRand = 1;
	int enemyMinRand = 0;
	int enemyType = rand() % (enemyMaxRand - enemyMinRand + 1) + enemyMinRand;
	Player* player = GameManager::getPlayer();
	auto position_player = player->getSprite()->getPosition();
	Vec2 position = Vec2(position_player.x+100, 650);


	Obstacles* enemy = NULL;
	switch (enemyType) {

	case Obstacles::Bomb:
		enemy = new Bomb();
		break;
	default:
		enemy = new Bomb();
		break;
	}

	enemy->getSprite()->setPosition(position);
	GameManager::world->addChild(enemy->getSprite());
	enemy->init();

	enemies.push_back(enemy);
	obstacles.push_back(enemy);
}

void GameManager::spawnSawBlade() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int enemyMaxRand = 1;
	int enemyMinRand = 0;
	int enemyType = rand() % (enemyMaxRand - enemyMinRand + 1) + enemyMinRand;
	Player* player = GameManager::getPlayer();
	auto position_player = player->getSprite()->getPosition();
	
	Vec2 position ;

	if (position_player.x > visibleSize.width / 2) {
		position = Vec2(50, visibleSize.height*0.25);
	}
	else {
		position = Vec2(visibleSize.width-50, visibleSize.height*0.25);
	}


	Obstacles* enemy = NULL;
	switch (enemyType) {

	case Obstacles::SawBlade:
		enemy = new SawBlade();
		break;
	default:
		enemy = new SawBlade();
		break;
	}

	enemy->getSprite()->setPosition(position);
	GameManager::world->addChild(enemy->getSprite());
	enemy->init();

	enemies.push_back(enemy);
	obstacles.push_back(enemy);
}

void GameManager::update(float dt) {
	if (isPause) {
		pauseGame();
		return;
	}
	player->update(dt);
	for (Obstacles* enemy : enemies) {
		if (enemy != NULL) {
			enemy->update(dt);
		}
	}
	//this->time_req += cocos2d::Director::getInstance()->getDeltaTime;
}

void GameManager::addObstacles(Obstacles* obstacle) {
	auto foundEntity = std::find(obstacles.begin(), obstacles.end(), obstacle);
	if (foundEntity == obstacles.end()) {
		world->addChild(obstacle->getSprite());
		obstacles.push_back(obstacle);
	}
}
void GameManager::addEntity(Entity* entity) {
	auto foundEntity = std::find(entities.begin(), entities.end(), entity);
	if (foundEntity == entities.end()) {
		world->addChild(entity->getSprite());
		entities.push_back(entity);
	}
}
Obstacles* GameManager::findObstacles(Sprite* sprite) {
	for (Obstacles* obstacle : obstacles) {
		if (obstacle != NULL) {
			if (obstacle->getSprite() == sprite) return obstacle;
		}
	}

	return NULL;
}
Entity* GameManager::findEntity(Sprite* sprite) {
	for (Entity* entity : entities) {
		if (entity != NULL) {
			if (entity->getSprite() == sprite) return entity;
		}
	}

	return NULL;
}

void GameManager::destroyObstacles(Obstacles* obstacle) {
	auto _obstacle = std::find(obstacles.begin(), obstacles.end(), obstacle);
	auto _enemy = std::find(enemies.begin(), enemies.end(), obstacle);

	/*std::remove(entities.begin(), entities.end(), entity);
	std::remove(enemies.begin(), enemies.end(), entity);*/
	obstacle->destroy();
	delete obstacle;

	if (_obstacle != obstacles.end()) (*_obstacle) = NULL;
	if (_enemy != enemies.end()) (*_enemy) = NULL;
}

void GameManager::pauseGame() {
	// Pause player
	player->pause();

	// Pause entities
	for (Obstacles* obstacle : obstacles) {
		if (obstacle != NULL) {
			obstacle->pause();
		}
	}

	// Pause game world
	//world->pause();
}

void GameManager::resumeGame() {
	// Resume Player
	player->resume();

	// Resume entities
	for (Obstacles* obstacle : obstacles) {
		if (obstacle != NULL) {
			obstacle->resume();
		}
	}

	//world->resume();
}


void GameManager::end() {
	
	auto closingScene = ClosingScene::create();
	Director::getInstance()->replaceScene(closingScene);
}
//
void GameManager::pause() {
	isPause = true;
}

void GameManager::resume() {
	isPause = false;
	resumeGame();
}

//void GameManager::setMark(float mark) {
//	this->mark = mark;
//}
//float GameManager::getMark() {
//	return this->mark;
//}

