#ifndef __CLIFF_H__
#define __CLIFF_H__
#include "cocos2d.h"
#include "Configuration.h"
#include "MyBodyParser.h"
#include <string>
#include "Definitions.h"

USING_NS_CC;

class Obstacle : public Sprite{
private:
public:
	Obstacle();
	static Obstacle* create(std::string textureName, std::string body, std::string name_body_json);
};

#endif
