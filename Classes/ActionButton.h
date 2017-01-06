#ifndef ACTION_BUTTON_H_
#define	ACTION_BUTTON_H_

#include "cocos2d.h"
#include "Submarine.h"
#include <string>

using namespace cocos2d;

class ActionButton : public Sprite{
protected:
	Submarine* submarine;
	virtual bool beganTouch(Touch* touch, Event* event) { return true; };
	virtual void endTouch(Touch* touch, Event* event) {};
	
public:
	ActionButton() {}
	ActionButton(Submarine *submarine);
	~ActionButton() {};
	
	void addEvent();
};



#endif // !ACTION_BUTTON_H

