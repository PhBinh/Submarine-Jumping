#include "OverLayer.h"

void OverLayer::setScore(int _score)
{
	score = _score;
	scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
}

// on "init" you need to initialize your instance
bool OverLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	auto overPanel = Sprite::create(RES_NOTHING_BACKGROUND);
	overPanel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(overPanel);

	//Score
	scoreLabel = LabelTTF::create("0", "fonts/Minecrafter.ttf", 120);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() + 50);

	this->addChild(scoreLabel);

	//Button
	auto menuBtn = MenuItemImage::create(RES_UI_BUTTON_MENU, RES_UI_BUTTON_MENU, CC_CALLBACK_0(OverLayer::gotoMenuScene, this));
	auto replayBtn = MenuItemImage::create(RES_UI_BUTTON_REPLAY, RES_UI_BUTTON_REPLAY, CC_CALLBACK_0(OverLayer::gotoPlayScene, this));
	menuBtn->setScale(0.5);
	replayBtn->setScale(0.5);

	auto menu = Menu::create(menuBtn, replayBtn, nullptr);
	menu->alignItemsHorizontallyWithPadding(50);

	menu->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() - 50);

	this->addChild(menu);

    return true;
}

void OverLayer::gotoMenuScene()
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.25f, menuscene));
}

void OverLayer::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}
