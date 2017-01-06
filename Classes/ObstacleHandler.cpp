#include "ObstacleHandler.h"

void ObstacleHandler::createCliff() {
	string* obstacleTexture = Loader::loadRandomObstacles();
	
	upCliff = Obstacle::create(obstacleTexture[0], obstacleTexture[1], "obstacle");
	downCliff = Obstacle::create(obstacleTexture[2], obstacleTexture[3], "obstacle_down");

	upCliff->setPosition(
		origin.x + visibleSize.width + upCliff->getTexture()->getContentSize().width / 2,
		origin.y + 120
	);
	
	downCliff->setPosition(upCliff->getPositionX(), upCliff->getPositionY() + 350);
	
	layer->addChild(upCliff);
	layer->addChild(downCliff);
}

ObstacleHandler::ObstacleHandler(Layer* layer)
{
	this->layer = layer;
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	velocity = OBSTACLE_SPEED;

	createCliff();

	createScoreLine();	

	endPositionX = origin.x - upCliff->getTexture()->getContentSize().width / 2;
	isMoveFinished = false;

	upCliff->runAction(
		Sequence::createWithTwoActions(
			MoveTo::create(
					visibleSize.width / velocity, 
					Point(endPositionX, upCliff->getPositionY())), 
					CallFunc::create(CC_CALLBACK_0(ObstacleHandler::moveFinished, this)
				)
		)
	);

	downCliff->runAction(
		Sequence::createWithTwoActions(
			MoveTo::create(
				visibleSize.width / velocity, 
				Point(endPositionX, downCliff->getPositionY())), 
				CallFunc::create(CC_CALLBACK_0(ObstacleHandler::moveFinished, this)
			)
		)
	);
}

void ObstacleHandler::moveFinished()
{
	downCliff->removeFromParent();
	upCliff->removeFromParent();

	isMoveFinished = true;
}

void ObstacleHandler::createScoreLine() {
	scoreLine = Node::create();
	scoreLine->setPosition(
		Point(
			upCliff->getTexture()->getContentSize().width / 2,
			upCliff->getTexture()->getContentSize().height
		)
	);
	auto linebody = PhysicsBody::createBox(Size(1, 300), PhysicsMaterial(0, 0, 0));
	linebody->setDynamic(false);

	linebody->setCategoryBitmask(eObjectBitmask::LINE);
	linebody->setCollisionBitmask(0);
	linebody->setContactTestBitmask(eObjectBitmask::SUBMARINE);

	scoreLine->setPhysicsBody(linebody);

	upCliff->addChild(scoreLine);
}