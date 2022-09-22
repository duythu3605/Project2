#include "GameManager.h"
#include <cstdlib>
#include <ctime>
//#include <math.h>
#include "Sword.h"

#include "ClosingScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameManager::world = NULL;
	std::vector<Obstacles*> GameManager::enemies;
	std::vector<Obstacles*> GameManager::obstacles;
bool GameManager::isPause = false;

Player* GameManager::player = NULL;

GameManager::GameManager() {
}

GameManager::~GameManager() {

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
		}, 5, "SpawnEnemies");
	
}

void GameManager::spawnEnemies() {
	int enemyMaxRand = 1;
	int enemyMinRand = 0;
	int enemyType = rand() % (enemyMaxRand - enemyMinRand + 1) + enemyMinRand;

	
	
	//int positionX = random(100, 800);
	

	//Vec2 direction = Vec2(positionX, 800);
	//direction.normalize();
	//const float padding = 0;
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

void GameManager::update(float dt) {
	if (isPause) {
		//pauseGame();
		return;
	}
	player->update(dt);
	for (Obstacles* enemy : enemies) {
		if (enemy != NULL) {
			enemy->update(dt);
		}
	}
}

void GameManager::addObstacles(Obstacles* obstacle) {
	auto foundEntity = std::find(obstacles.begin(), obstacles.end(), obstacle);
	if (foundEntity == obstacles.end()) {
		world->addChild(obstacle->getSprite());
		obstacles.push_back(obstacle);
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
//
void GameManager::end() {
	auto closingScene = ClosingScene::create();
	Director::getInstance()->replaceScene(closingScene);
}
//
void GameManager::pause() {
	isPause = true;
}
//
void GameManager::resume() {
	isPause = false;
	resumeGame();
}

void GameManager::nextStage() {

}
