#include "ActionButton.h"

ActionButton::ActionButton(Submarine* submarine) {
	this->submarine = submarine;
}

void ActionButton::addEvent() {
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ActionButton::beganTouch, this);
	listener->onTouchEnded = CC_CALLBACK_2(ActionButton::endTouch, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

