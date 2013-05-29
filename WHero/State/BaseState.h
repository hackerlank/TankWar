/*
 * BaseState.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#ifndef BASESTATE_H_
#define BASESTATE_H_

#include <OIS.h>
#include <Ogre.h>


class BaseState 
{
public:
	virtual ~BaseState();

	virtual void enter(void)	= 0;
	virtual void exit(void)		= 0;

	virtual void pause(void){}
	virtual void resume(void){}

	virtual bool keyPressed(const OIS::KeyEvent&evt);
	virtual bool keyReleased(const OIS::KeyEvent&evt);
	virtual bool mouseMoved(const OIS::MouseEvent&evt);
	virtual bool mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id);

	virtual void update(float timeSinceLastFrame) = 0;

	void changeState(BaseState *newState);
	void pushState(BaseState *newState);
	void popState();

protected:
	BaseState();
};
#endif