#ifndef __LOADER_H__
#define __LOADER_H__

#include "cocos2d.h"
#include "MyBodyParser.h"
#include "Configuration.h"
#include <string>

USING_NS_CC;
using namespace std;

static class Loader {
private:
	float holdTimeX;
	float holdTimeY;
	
public:
	static Animate* loadAnimations(const char* spriteSheetName, int numberOfPics);
	static string* loadRandomObstacles();
};

#endif 