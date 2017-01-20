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
	void moveObstacles(float dt);
	void deleteObstacles();
	void createObstacles();
	void refreshObstacles();

private:
	std::list<Obstacle*> obstacles;
	Size visibleSize;
	Vec2 origin;
	Layer* layer;

	int randInrange(int min, int max) {
		return min + (std::rand() % (max - min + 1));
	}
};

#endif //__OBSTACLE_H__