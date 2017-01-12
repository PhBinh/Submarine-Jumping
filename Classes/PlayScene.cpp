#include "PlayScene.h"
#include <iostream>
Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//Debug the collision (draw bit mask to view collision).

	if (TURN_ON_TEST)
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);	
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void PlayScene::backgroundInit() {
	float initX = origin.x + visibleSize.width / 2;
	
	for (int i = 0; i < 3; i++) {
		Sprite* background = Sprite::create(RES_BACKGROUND);
		float width = background->getContentSize().width;
		background->setPosition(initX + width * i, origin.y + visibleSize.height / 2);
		backgrounds[i] = background;
		this->addChild(background);
	}
}


void PlayScene::backgroundMove(float dt) {
	bool isBackgroundOver = false;

	for (int i = 0; i < 3; i++) {
		Sprite* bg = backgrounds[i];
		Point bgPos = bg->getPosition();

		float width = backgrounds[0]->getContentSize().width;
		if (i == 0 && backgrounds[0]->getPosition().x <= -width) {
			isBackgroundOver = true;
		}

		if (isBackgroundOver)
			bgPos.x += width;
		else 
			bgPos.x -= SCENE_SPEED;

		bgPos.x = (int)bgPos.x;
		bg->setPosition(bgPos);
	}
}

bool PlayScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	isDead = false;
	isHitShark = false;

	backgroundInit();

	//Player
	submarine = new Submarine(this);
	Sprite* trueSubmarine = submarine->getSubmarine();
	
	Point jumpButtonPosition(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height / 4);
	JumpButton* jumpButton = JumpButton::create(submarine, RES_UI_BUTTON_INCREASE_Y, jumpButtonPosition);
	this->addChild(jumpButton);

	Point goForwardButtonPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 4);
	IncSpeedButton* incSpeedButton = IncSpeedButton::create(submarine, RES_UI_BUTTON_INCREASE_X, goForwardButtonPosition);
	this->addChild(incSpeedButton);

	//Shark
	shark = Shark::sharkCreate(submarine);
	this->addChild(shark);

	//Contact listener
	auto contactListener = EventListenerPhysicsContact::create();
	
	//Collision.
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Update Display.
	this->scheduleUpdate();
	this->schedule(schedule_selector(PlayScene::createPipe, this), 2.0f);
	this->schedule(schedule_selector(PlayScene::backgroundMove, this), 1/60);
	listPipes.push_back(new ObstacleHandler(this));

	//Score
	score = 0;
	scoreLabel = LabelTTF::create("0", "fonts/Minecrafter.ttf", 100);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 6) * 5);

	this->addChild(scoreLabel, 50);

    return true;
}

void PlayScene::update(float dt)
{
	
	for (std::list<ObstacleHandler*>::iterator pipe = listPipes.begin(); pipe != listPipes.end(); pipe++)
	{
		if ((*pipe)->isMoveFinished)
		{
			CC_SAFE_DELETE((*pipe));
			listPipes.remove(*pipe);
			break;
		}
	}

	submarine->Update(dt);
	shark->move(submarine);

	if (isDead || submarine->isDead || isHitShark)
	{
		submarine->destroyProceed();

		if (isHitShark)
			shark->hitProceed();

		this->removeChild(scoreLabel);
		this->pause();

		auto childs = this->getChildren();
		for each (auto child in childs)
		{
			child->pause();
		}

		auto overlayer = OverLayer::create();
		overlayer->setScore(score);

		overlayer->setPosition(origin.x, origin.y);
		this->addChild(overlayer, 110);
	}
	
}


void PlayScene::onExit()
{
	Layer::onExit();

	CC_SAFE_DELETE(submarine);
	
	while (!listPipes.empty())
	{
		CC_SAFE_DELETE(listPipes.front());
		listPipes.pop_front();
	}
}

void PlayScene::createPipe(float dt)
{
	listPipes.push_back(new ObstacleHandler(this));
}

void PlayScene::submarineDestroyed(float dt) {
	submarine->destroyProceed();
}

bool PlayScene::onContactBegin(PhysicsContact &contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	if ((shapeA->getCategoryBitmask() == eObjectBitmask::OBSTACLE && shapeB->getCategoryBitmask() == eObjectBitmask::SUBMARINE) ||
		(shapeB->getCategoryBitmask() == eObjectBitmask::OBSTACLE && shapeA->getCategoryBitmask() == eObjectBitmask::SUBMARINE))
	{
		if (TURN_ON_TEST)
			isDead = false;
		else isDead = true;
	}
	else if ((shapeB->getCategoryBitmask() == eObjectBitmask::SHARK && shapeA->getCategoryBitmask() == eObjectBitmask::SUBMARINE) ||
			 (shapeB->getCategoryBitmask() == eObjectBitmask::SHARK && shapeA->getCategoryBitmask() == eObjectBitmask::SUBMARINE))
	{
		if (TURN_ON_TEST)
			isDead = false;
		else
		{
			isDead = true;
			isHitShark = true;
		}
	}
	else
	{
		if ((shapeA->getCategoryBitmask() == eObjectBitmask::LINE && shapeB->getCategoryBitmask() == eObjectBitmask::SUBMARINE) ||
			(shapeB->getCategoryBitmask() == eObjectBitmask::LINE && shapeA->getCategoryBitmask() == eObjectBitmask::SUBMARINE))
		{
			score++;
			scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		}
	}


	return true;
}
