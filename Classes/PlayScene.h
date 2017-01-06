#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Submarine.h"
#include "ObstacleHandler.h"
#include "MenuScene.h"
#include "OverLayer.h"
#include "Configuration.h"
#include <map>
#include "IncSpeedButton.h"
#include "JumpButton.h"
USING_NS_CC;

class PlayScene : public cocos2d::Layer
{
private:
	//Scene Handling Variables.

	float globalTimer;
	bool isScene1 = true;
	Size visibleSize;
	Vec2 origin;
	Sprite* backgrounds[3];
	LabelTTF* scoreLabel;
	int score;

	IncSpeedButton* incSpeedButton;

	//Objects Handling Variables.
	Submarine* submarine;
	bool isDead;
	std::list<ObstacleHandler*> listPipes;


	void backgroundInit();
	void backgroundMove(float dt);

	void submarineDestroyed(float dt);
	void createPipe(float dt);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(PlayScene);

	void onMouseDown(Event* _event);
	void update(float dt);
	void onExit();
	bool onContactBegin(PhysicsContact &contact);
};

#endif // __PLAY_SCENE_H__
