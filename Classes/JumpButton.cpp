#include "JumpButton.h"

bool JumpButton::beganTouch(Touch* touch, Event* event) {
	auto target = this;
	int testOpacity = this->getOpacity();
	//TODO:
	/*
	-> Save the time from the beginning to released-state.
	-> Check the required steps for:
	Recalculating the seri of obstacles.
	---Description---:
	-(The required steps will be stored in the configuration).
	-(The ObstacleHandler will calculate the step current step by checking the number of obstacle
	which is out range).
	-(All obstacles will be arranged along the Orbit).
	*/

	//Get the position of the current point relative to the button
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//Check the click area
	if (rect.containsPoint(locationInNode))
	{
		submarine->goUp();
		target->setOpacity(180);
		return true;
	}
}

void JumpButton::endTouch(Touch* touch, Event* event) {
	submarine->stopGoUp();

	//TODO:
	/*
		This block will implement the function to calculate the position for generation the first obstacle in the 
		seri of the obstacles created by rhythm base function.
		-->
			Calculate hold-time.
	*/
	

	this->setOpacity(255);
}

JumpButton::JumpButton(Submarine* submarine) : ActionButton(submarine) {
}

JumpButton* JumpButton::create(Submarine* submarine, std::string texture, Point position)
{
	JumpButton* actionButton = new JumpButton(submarine);

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

void JumpButton::initOptions(Point position) {
	this->setPosition(position);
	this->setScale(0.4f);
}