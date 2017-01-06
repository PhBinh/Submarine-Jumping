#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include "cocos2d.h"
#include "Definitions.h"
#include "Configuration.h"
#include "Loader.h"

USING_NS_CC;

class Submarine
{
public:
	Submarine(Layer* layer);
	void goUp();
	void goForward();

	void stopGoUp();

	void stopGoForward();

	void Update(float dt);
	bool isDead;

	Sprite* getSubmarine() { return submarine; }
	
	void destroyProceed();
	float getCurrentVelocityX();
	float getCurrentVelocityY();

private:
	float height;
	float width;
	float scale;
	
	Sprite* submarineTexture;
	Sprite* submarine;

	Size visibleSize;
	Vec2 origin;

	bool isIncVelXRequested;
	bool isIncVelYRequested;
	float timeIncX;
	float timeIncY;


	Vec2 velocity;
	Vec2 acceleration;
	float rotation;
	
	void goUpHandling(float dt);
	void goForwardHandling(float dt);

	PhysicsBody* createPhysicalBody();
	void removeAllChildren();
};

#endif 