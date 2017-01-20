#include "Submarine.h"

void Submarine::destroyProceed() {
	texture->stopAllActions();
	texture->setTexture(RES_ENTITY_SUBMARINE_DAMAGED_FIRST_TEXTURE);

	Animate *animaction = Loader::loadAnimations(RES_ENTITY_SUBMARINE_DAMAGED, 6);
	Repeat *reptaction = Repeat::create(animaction, 1);

	texture->runAction(
		Sequence::createWithTwoActions(
			reptaction,
			CallFunc::create(CC_CALLBACK_0(Submarine::removeAllChildren, this))
		)
	);
}

void Submarine::initial() {
	origin = Director::sharedDirector()->getVisibleOrigin();
	visibleSize = Director::sharedDirector()->getVisibleSize();
	texture = Sprite::create(RES_ENTITY_SUBMARINE_FIRST_TEXTURE);

	scale = SUBMARINE_SCALE;
	timeIncX = 0;
	timeIncY = 0;
	isIncVelXRequested = false;
	isIncVelYRequested = false;

	height = texture->getContentSize().height * scale;
	width = texture->getContentSize().width * scale;

	//Create Idle Actions.
	Animate* animation = Loader::loadAnimations(RES_ENTITY_SUBMARINE, 6);
	RepeatForever *reptAction = RepeatForever::create(animation);
	texture->runAction(reptAction);

	auto submarineBody = Loader::createPhysicalBody(this, RES_ENTITY_SUBMARINE_BODY, "submarine", eObjectBitmask::SUBMARINE);

	//Prepare the models: connect submarine body with the texture.
	//Anchor points must be setted to fit the position of texture into the physical body.
	this->setAnchorPoint(Vec2(0, 0));
	texture->setAnchorPoint(Vec2(0, 0));
	this->addChild(texture);
	this->setPhysicsBody(submarineBody);
	this->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	this->setScale(scale);

	isDead = false;
	velocity = Vec2(0, 0);
	rotation = 0.0f;
}

Submarine* Submarine::createSubmarine()
{
	Submarine* submarine = new Submarine();
	
	if (submarine->initWithFile(RES_NOTHING_BACKGROUND))
	{
		submarine->autorelease();
		submarine->initial();

		return submarine;
	}

	CC_SAFE_DELETE(submarine);
	return NULL;
}

void Submarine::goUpHandling(float dt) {
	bool isOutOfDownBound = false;

	if (isIncVelYRequested)
	{
		if (this->getPositionY() < visibleSize.height - height)
			acceleration.y += SUBMARINE_ACCELERATION_Y + SUBMARINE_SMOOTH_ACCELERATION * dt;
			
	}
	else
	{
		if (this->getPositionY() > height / 4)
		{
			acceleration.y += GRAVITY_FACTOR;
		}
		else
		{			
			isOutOfDownBound = true;
			if (TURN_ON_TEST)
				isDead = false;
			else isDead = true;
		}
	}

	if (!isOutOfDownBound)
	{
		velocity.y = SUBMARINE_SPEED_Y + acceleration.y * dt / 2;
	}
	else
		velocity.y = 0;

	float nextPositionY = this->getPositionY() + velocity.y;

	if (nextPositionY >= visibleSize.height - height)
		nextPositionY = visibleSize.height - height;

	this->setPosition(Point(this->getPositionX(), nextPositionY));
	this->setRotation(rotation);
}

void Submarine::goForwardHandling(float dt){
	if (isIncVelXRequested) {
		acceleration.x += SUBMARINE_ACCELERATION_X + SUBMARINE_SMOOTH_ACCELERATION * dt;
	}

	else {

		if (this->getPositionX() > visibleSize.width / 4)
		{
			acceleration.x += GRAVITY_FACTOR;
		}
		else
			velocity.x = 0;
	}

	velocity.x = SUBMARINE_SPEED_X + acceleration.x * dt / 2;

	float nextPositionX = this->getPositionX() + velocity.x;

	if (nextPositionX >= visibleSize.width - width)
	{
		nextPositionX = visibleSize.width - width;
	}

	else if(nextPositionX <= width / 3)
	{
		nextPositionX = width / 3;
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
	this->setPosition(Point(nextPositionX, this->getPositionY()));
	this->setRotation(rotation);
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