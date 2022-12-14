#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "ui/CocosGUI.h" 

class GameScene : public cocos2d::Scene
{
public:
	Player* player;
	Node* playerInfo;
	Camera* cameraUI;
	Vec2 position;
	float time_req = 0;
	float time;
	int heart_req = 0;
	string mark;
	Label* textMark;
	string heart;
	Label* textHeart;
	

	bool onContactBegin(PhysicsContact& contact);
	void onContactSeparate(PhysicsContact& contact);
	void initContactListener();
	void initPlayerInfoUI();
	void updatePlayerInfo();
	void initPauseMenu();
	//void followPlayer();
	void PrePosition();
	void PreRotation();
	void initCameraUI();
	void initBackground();
	Vec2 getPositionP();
	void initYard();
	void Time_req();
	void setTime_req(float time);
	float getTime_req();
	void setMark(string mark);
	string getMark();
	void initMarkUI();
	void Heart_req();
	void setHeart_req(int heart_req);
	int getHeart_req();
	void setHeartUI(string heart);
	string getHeartUI();
	void initHeartUI();
	void level(float time);
	
	

	cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
