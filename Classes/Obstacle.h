#ifndef __CLIFF_H__
#define __CLIFF_H__
#include "cocos2d.h"
#include "Configuration.h"
#include "MyBodyParser.h"
#include <string>
#include "Definitions.h"
#include "Loader.h"

using namespace std;
USING_NS_CC;

class Obstacle : public Sprite{
private:
	bool IsMoveFinished;
	Sprite* topTexture;
	Sprite* belowTexture;
	Sprite* scoreLine;
	float velocity;

	void createScoreLine();
	void initialize();
	void createTexture(Sprite*& texture, std::string textureName, std::string body, std::string name_body_json);

public:
	Obstacle();
	~Obstacle() {}
	void moveFinished();
	void move(float dt);
	bool isMoveFinished();
	void reposition(float middleDistance);

	static Obstacle* create();
};

#endif
