#ifndef _SHARK_H_
#define _SHARK_H_

#include "cocos2d.h"
#include "Definitions.h"
#include "Configuration.h"
#include "Loader.h"
#include "Submarine.h"

USING_NS_CC;

class Shark : public Sprite {
private:
	Sprite* texture;
	float height;
	float width;
public:
	static Shark* sharkCreate(Submarine* submarine);

	void hitProceed();
	void setTextureChild(Sprite* texture);
	void move(Submarine* submarine);
};

#endif 