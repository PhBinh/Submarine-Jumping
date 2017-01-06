#include "Obstacle.h"

Obstacle::Obstacle() {}

Obstacle* Obstacle::create(std::string textureName, std::string body, std::string name_body_json) {
	Obstacle* texture = new Obstacle();
	texture->initWithFile(textureName);

	MyBodyParser::getInstance()->parseJsonFile(body);
	auto bottomBody = MyBodyParser::getInstance()->bodyFormJson(texture, name_body_json, PhysicsMaterial(0, 0, 0));

	bottomBody->setDynamic(false);
	bottomBody->setCategoryBitmask(eObjectBitmask::OBSTACLE);
	bottomBody->setCollisionBitmask(0);
	bottomBody->setContactTestBitmask(eObjectBitmask::SUBMARINE);
	texture->setPhysicsBody(bottomBody);

	texture->setScaleY(0.7);
	texture->setScaleX(0.3);

	return texture;
}
