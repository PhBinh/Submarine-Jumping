#include "Obstacle.h"

bool Obstacle::isMoveFinished() {
	return IsMoveFinished;
}

void Obstacle::moveFinished() {
	IsMoveFinished = true;
}

void Obstacle::move(float dt) {
	float obstaclePositionX = this->getPositionX();

	//set the position of obstacle to be minus base on velocity.
	this->setPositionX(obstaclePositionX - velocity * dt);

	if (obstaclePositionX <= 0)
		moveFinished();
}

void Obstacle::initialize() {
	string* obstacleTexture = Loader::loadRandomObstacles();

	createTexture(belowTexture, obstacleTexture[0], obstacleTexture[1], "obstacle");
	createTexture(topTexture, obstacleTexture[2], obstacleTexture[3], "obstacle_down");
	createScoreLine();

	belowTexture->setPositionY(-100);
	topTexture->setPositionY(300);

	this->addChild(topTexture);
	this->addChild(belowTexture);
	belowTexture->addChild(scoreLine);
}

Obstacle::Obstacle() {
	velocity = OBSTACLE_SPEED;
	IsMoveFinished = false;

	initialize();
}

void Obstacle::createTexture(Sprite* &texture, std::string textureName, std::string body, std::string name_body_json) {
	texture = Sprite::create();
	texture->setTexture(textureName);

	MyBodyParser::getInstance()->parseJsonFile(body);
	auto bottomBody = MyBodyParser::getInstance()->bodyFormJson(texture, name_body_json, PhysicsMaterial(0, 0, 0));

	bottomBody->setDynamic(false);
	bottomBody->setCategoryBitmask(eObjectBitmask::OBSTACLE);
	bottomBody->setCollisionBitmask(0);
	bottomBody->setContactTestBitmask(eObjectBitmask::SUBMARINE);
	texture->setPhysicsBody(bottomBody);
	texture->setAnchorPoint(Point(0,0));
	texture->setScaleY(0.7);
	texture->setScaleX(0.3);
}

void Obstacle::createScoreLine() {
	scoreLine = Sprite::create();

	scoreLine->setPosition(
		Point(
			topTexture->getTexture()->getContentSize().width / 2,
			topTexture->getTexture()->getContentSize().height
		)
	);

	auto linebody = PhysicsBody::createBox(Size(1, 300), PhysicsMaterial(0, 0, 0));
	linebody->setDynamic(false);

	linebody->setCategoryBitmask(eObjectBitmask::LINE);
	linebody->setCollisionBitmask(0);
	linebody->setContactTestBitmask(eObjectBitmask::SUBMARINE);

	scoreLine->setPhysicsBody(linebody);
}

Obstacle* Obstacle::create() {
	Obstacle* obstacle = new Obstacle();

	if (obstacle->init())
	{
		obstacle->autorelease();

		return obstacle;
	}

	CC_SAFE_DELETE(obstacle);
	return NULL;
}

void Obstacle::reposition(float middleDistance) {
	IsMoveFinished = false;

	belowTexture->setPositionY(Loader::loadRandomFloat(-100, -60));
	topTexture->setPositionY(Loader::loadRandomFloat(280, 350));
}