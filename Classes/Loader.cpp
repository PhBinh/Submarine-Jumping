#include "Loader.h"

Animate* Loader::loadAnimations(const char* spriteSheetName, int numberOfPics) {
	Animation *animate = Animation::create();
	for (int i = 1; i <= numberOfPics; i++)
	{
		char frameName[128] = { 0 };
		sprintf(frameName, spriteSheetName, i);
		animate->addSpriteFrameWithFileName(frameName);
	}

	animate->setDelayPerUnit(0.1f);
	animate->setRestoreOriginalFrame(true);

	Animate *animaction = Animate::create(animate);

	return animaction;
}



string* Loader::loadRandomObstacles() {
	int type = 1; // randInrange(1, 4);
	string* result = new string[4];

	switch (type)
	{
		case 1:
			result[0] = RES_ENTITY_OBSTACLE_ROCK_UP;
			result[1] = RES_ENTITY_OBSTACLE_ROCK_UP_BODY;
			result[2] = RES_ENTITY_OBSTACLE_ROCK_DOWN;
			result[3] = RES_ENTITY_OBSTACLE_ROCK_DOWN_BODY;

			return result;
		default:
			return NULL;
	}
}

PhysicsBody* Loader::createPhysicalBody(Sprite* entity, string json_file, string name_inside_json_file, int eObjBitmask) {
	MyBodyParser::getInstance()->parseJsonFile(json_file);
	auto entityBody = MyBodyParser::getInstance()->bodyFormJson(entity, name_inside_json_file, PhysicsMaterial(0, 0, 0));
	entityBody->setCategoryBitmask(eObjBitmask);

	if (eObjBitmask == eObjectBitmask::SHARK)
		entityBody->setContactTestBitmask(eObjectBitmask::OBSTACLE | eObjectBitmask::SUBMARINE);
	else
		entityBody->setContactTestBitmask(eObjectBitmask::OBSTACLE | eObjectBitmask::LINE | eObjectBitmask::SHARK);

	return entityBody;
}


float Loader::loadRandomFloat(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
	//return min + (std::rand() % (max - min + 1));
}