#ifndef GO_FORWARD_BUTTON_H_
#define GO_FORWARD_BUTTON_H_

#include "ActionButton.h"

class IncSpeedButton : public ActionButton {
private:
	bool beganTouch(Touch* touch, Event* event);
	void endTouch(Touch* touch, Event* event);
public:
	static IncSpeedButton* create(Submarine* submarine, std::string texture, Point position);
	void initOptions(Point position);
	IncSpeedButton(Submarine* submarine);
	~IncSpeedButton() {};
};

#endif