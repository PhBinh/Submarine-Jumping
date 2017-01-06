#ifndef JUMP_BUTTON_H_
#define JUMP_BUTTON_H_

#include "ActionButton.h"

class JumpButton : public ActionButton {
private:
	bool beganTouch(Touch* touch, Event* event);
	void endTouch(Touch* touch, Event* event);
public:
	static JumpButton* create(Submarine* submarine, std::string texture, Point position);
	void initOptions(Point position);
	JumpButton(Submarine* submarine);
	~JumpButton() {};
};

#endif
