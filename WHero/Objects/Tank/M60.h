#ifndef TANK_M60_H
#define TANK_M60_H

#include "BaseTank.h"

class M60 : public BaseTank
{
public:
	M60(const std::string&);
	virtual ~M60(void);

	void Update();

	bool keyPressed(const OIS::KeyEvent&evt);
	bool keyReleased(const OIS::KeyEvent&evt);
	bool mouseMoved(const OIS::MouseEvent&evt);
	bool mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id);
};

#endif