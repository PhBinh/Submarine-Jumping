#include "IncSpeedButton.h"

bool IncSpeedButton::beganTouch(Touch* touch, Event* event) {
	//Get the position of the current point relative to the button
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());
	Size s = this->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//Check the click area
	if (rect.containsPoint(locationInNode))
	{
		submarine->goForward();
		this->setOpacity(180);
		return true;
	}
}

void IncSpeedButton::endTouch(Touch* touch, Event* event) {
	submarine->stopGoForward();
	this->setOpacity(255);
}

IncSpeedButton::IncSpeedButton(Submarine* submarine) : ActionButton(submarine) {
}

IncSpeedButton* IncSpeedButton::create(Submarine* submarine, std::string texture, Point position)
{
	IncSpeedButton* actionButton = new IncSpeedButton(submarine);

	if (actionButton->initWithFile(texture))
	{
		actionButton->autorelease();

		actionButton->initOptions(position);

		actionButton->addEvent();

		return actionButton;
	}

	CC_SAFE_DELETE(actionButton);
	return NULL;
}

void IncSpeedButton::initOptions(Point position) {
	this->setPosition(position);
	this->setScale(0.4f);
}