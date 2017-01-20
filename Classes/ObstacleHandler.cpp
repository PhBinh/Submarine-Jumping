#include "ObstacleHandler.h"

void ObstacleHandler::moveObstacles(float dt) {

	for (std::list<Obstacle*>::iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); obstacle++)
	{
		if ((*obstacle)->isMoveFinished())
		{
 			obstacles.sort([](Obstacle * lhs, Obstacle* rhs) {return lhs->getPositionX() < rhs->getPositionX(); });
			Obstacle* last = obstacles.back();
			float randDis = Loader::loadRandomFloat(300, 700);
			(*obstacle)->setPositionX(last->getPositionX() + randDis);

			float randomSpace = Loader::loadRandomFloat(20, 50);
			(*obstacle)->reposition(randomSpace);

			break;
		}
		else
			(*obstacle)->move(dt);
	}
}

ObstacleHandler::ObstacleHandler(Layer* layer)
{
	this->layer = layer;
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
}

void ObstacleHandler::deleteObstacles() {
	while (!obstacles.empty())
	{
		CC_SAFE_DELETE(obstacles.front());
		obstacles.pop_front();
	}
}

void ObstacleHandler::createObstacles() {
	float randDistance = Loader::loadRandomFloat(400, 600);
	for (int i = 0; i < 5; i++)
	{
		Obstacle* obstacle = Obstacle::create();
		obstacle->setPosition(
			origin.x + 300 + randDistance * (i + 1),
			origin.y
		);

		layer->addChild(obstacle);
		obstacles.push_back(obstacle);
	}
}

void ObstacleHandler::refreshObstacles() {
	float randDistance = Loader::loadRandomFloat(400, 600);
	int i = 0;
	for (std::list<Obstacle*>::iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); obstacle++)
	{
		(*obstacle)->setPosition(
			origin.x + 300 + randDistance * ++i,
			origin.y
		);
	}
}
