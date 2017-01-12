#include "Shark.h"

Shark* Shark::sharkCreate(Submarine* submarine){
	Shark* shark = new Shark();
	Sprite* shark_texture = Sprite::create(RES_ENTITY_SUBMARINE_FIRST_TEXTURE);

	if (shark->initWithFile(RES_NOTHING_BACKGROUND))
	{
		shark->autorelease();
	
		shark->height = shark->getContentSize().height * SHARK_SCALE;
		shark->width = shark->getContentSize().width * SHARK_SCALE;

		//Create Idle Actions.
		Animate* animation = Loader::loadAnimations(RES_ENTITY_SHARK, 9);
		RepeatForever *reptAction = RepeatForever::create(animation);
		shark_texture->runAction(reptAction);

		auto sharkPhysicalBody = Loader::createPhysicalBody(shark, RES_ENTITY_SHARK_BODY, "shark", eObjectBitmask::SHARK);
		
		//Prepare the models: connect submarine body with the texture.
		//Anchor points must be setted to fit the position of texture into the physical body.
		shark->setAnchorPoint(Vec2(0, 0));
		shark_texture->setAnchorPoint(Vec2(0, 0));
		shark_texture->setFlippedX(true);
		shark->setTextureChild(shark_texture);
		shark->setPhysicsBody(sharkPhysicalBody);
		shark->setPosition(-shark->width / 6, submarine->getSubmarine()->getPositionY() - shark->height / 2);
		shark->setScale(SHARK_SCALE);
		shark->setRotation(-25);
		return shark;
	}

	CC_SAFE_DELETE(shark);
	return NULL;
}

void Shark::move(Submarine* submarine) {
	this->setPosition(-width / 6, submarine->getSubmarine()->getPositionY() - height / 2);
}

void Shark::setTextureChild(Sprite* texture) {
	this->texture = texture;
	this->addChild(this->texture);
}

void Shark::hitProceed() {
	texture->stopAllActions();
	texture->setTexture(RES_ENTITY_SHARK_HIT_FIRST_TEXTURE);

	Animate *animaction = Loader::loadAnimations(RES_ENTITY_SHARK_HIT, 9);
	Repeat *reptaction = Repeat::create(animaction, 1);

	texture->runAction(
		Sequence::createWithTwoActions(
			reptaction,
			CallFunc::create(CC_CALLBACK_0(Shark::removeAllChildren, this))
		)
	);
}