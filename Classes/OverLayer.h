#ifndef __OVER_LAYER_H__
#define __OVER_LAYER_H__

#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

class OverLayer : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(OverLayer);

	void setScore(int _score);

private:
	void gotoMenuScene(); 
	void gotoPlayScene();
	int score;
	LabelTTF* scoreLabel;
};

#endif // __OVER_LAYER_H__
