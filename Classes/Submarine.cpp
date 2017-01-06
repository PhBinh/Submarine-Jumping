#include "Submarine.h"

void Submarine::destroyProceed() {
	submarineTexture->stopAllActions();
	submarineTexture->setTexture(RES_ENTITY_SUBMARINE_DAMAGED_FIRST_TEXTURE);

	Animate *animaction = Loader::loadAnimations(RES_ENTITY_SUBMARINE_DAMAGED, 6);
	Repeat *reptaction = Repeat::create(animaction, 1);

	submarineTexture->runAction(
		Sequence::createWithTwoActions(
			reptaction,
			CallFunc::create(CC_CALLBACK_0(Submarine::removeAllChildren, this))
		)
	);
}

void Submarine::removeAllChildren() {
	submarine->removeAllChildren();
}


PhysicsBody* Submarine::createPhysicalBody() {
	MyBodyParser::getInstance()->parseJsonFile(RES_ENTITY_SUBMARINE_BODY);
	auto submarineBody = MyBodyParser::getInstance()->bodyFormJson(submarine, "submarine", PhysicsMaterial(0, 0, 0));
	submarineBody->setCategoryBitmask(eObjectBitmask::SUBMARINE);
	submarineBody->setContactTestBitmask(eObjectBitmask::OBSTACLE | eObjectBitmask::LINE);

	return submarineBody;
}

Submarine::Submarine(Layer* layer)
{
	origin = Director::sharedDirector()->getVisibleOrigin();
	visibleSize = Director::sharedDirector()->getVisibleSize();

	scale = SUBMARINE_SCALE;
	timeIncX = 0;
	timeIncY = 0;
	isIncVelXRequested = false;
	isIncVelYRequested = false;
	
	submarine = Sprite::create(RES_NOTHING_BACKGROUND);	
	
	submarineTexture = Sprite::create(RES_ENTITY_SUBMARINE_FIRST_TEXTURE);
	
	height = submarineTexture->getContentSize().height * scale;
	width = submarineTexture->getContentSize().width * scale;

	//Create Idle Actions.
	Animate* animation = Loader::loadAnimations(RES_ENTITY_SUBMARINE, 6);
	RepeatForever *reptAction = RepeatForever::create(animation);
	submarineTexture->runAction(reptAction);
		
	auto submarineBody = createPhysicalBody();
	
	//Prepare the models: connect submarine body with the texture.
	//Anchor points must be setted to fit the position of texture into the physical body.
	submarine->setAnchorPoint(Vec2(0, 0));
	submarineTexture->setAnchorPoint(Vec2(0, 0));
	submarine->addChild(submarineTexture);
	submarine->setPhysicsBody(submarineBody);
	submarine->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	submarine->setScale(scale);
	layer->addChild(submarine, 100);

	isDead = false;
	velocity = Vec2(0, 0);
	rotation = 0.0f;
}

void Submarine::goUpHandling(float dt) {
	if (isIncVelYRequested)
	{
		if (submarine->getPositionY() < visibleSize.height - height)
			acceleration.y += SUBMARINE_ACCELERATION_Y + SUBMARINE_SMOOTH_ACCELERATION * dt;
			
	}
	else
	{
		if (submarine->getPositionY() > height / 4)
		{
			acceleration.y += GRAVITY_FACTOR;
		}
		else
		{
			velocity.y = 0;
			
			if (TURN_ON_TEST)
				isDead = false;
			else isDead = true;
		}
	}

	velocity.y = SUBMARINE_SPEED_Y + acceleration.y * dt / 2;

	float nextPositionY = submarine->getPositionY() + velocity.y;

	if (nextPositionY >= visibleSize.height - height)
		nextPositionY = visibleSize.height - height;

	submarine->setPosition(Point(submarine->getPositionX(), nextPositionY));
	submarine->setRotation(rotation);
}

void Submarine::goForwardHandling(float dt){
	if (isIncVelXRequested) {
		acceleration.x += SUBMARINE_ACCELERATION_X + SUBMARINE_SMOOTH_ACCELERATION * dt;
	}

	else {

		if (submarine->getPositionX() > visibleSize.width / 4)
		{
			acceleration.x += GRAVITY_FACTOR;
		}
		else
			velocity.x = 0;
	}

	velocity.x = SUBMARINE_SPEED_X + acceleration.x * dt / 2;

	float nextPositionX = submarine->getPositionX() + velocity.x;

	if (nextPositionX >= visibleSize.width - width)
	{
		nextPositionX = visibleSize.width - width;
	}

	if (TURN_ON_TEST) {
		log("---------------Time Increase Y : ------------");
		log(timeIncY);
		log("---------------Delta Time : ------------");
		log(dt);
		log("---------------Acceleration Y : ------------");
		log(acceleration.y);
		log("---------------Velocity Y : ------------");
		log(velocity.y);
	}
	submarine->setPosition(Point(nextPositionX, submarine->getPositionY()));
	submarine->setRotation(rotation);
}

void Submarine::Update(float dt)
{
	goUpHandling(dt);
	goForwardHandling(dt);
}

void Submarine::goUp()
{
	isIncVelYRequested = true;
}


void Submarine::goForward()
{
	isIncVelXRequested = true;
}

void Submarine::stopGoUp() {
	isIncVelYRequested = false;
}

void Submarine::stopGoForward() {
	isIncVelXRequested = false;
}

float Submarine::getCurrentVelocityX() {
	return velocity.x;
}
float Submarine::getCurrentVelocityY() {
	return velocity.y;
}