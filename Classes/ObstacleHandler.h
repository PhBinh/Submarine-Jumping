#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Configuration.h"
#include "MyBodyParser.h"
#include "Obstacle.h"
#include "Loader.h"

USING_NS_CC;

class ObstacleHandler
{
public:
	ObstacleHandler(Layer* layer);
	void moveFinished();
	bool isMoveFinished;

private:
	Obstacle* upCliff;
	Obstacle* downCliff;
	Node* scoreLine;
	
	Size visibleSize;
	Vec2 origin;
	Layer* layer;

	float velocity;
	float endPositionX;

	void createCliff();
	void createScoreLine();
};

#endif //__PIPE_H__