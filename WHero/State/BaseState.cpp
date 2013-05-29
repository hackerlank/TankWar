/*
 * BaseState.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#include "BaseState.h"
#include "StateManager.h"
#include "../GUI/MyGUIManager.h"

BaseState::BaseState()
{

}

BaseState::~BaseState()
{

}

void BaseState::changeState(BaseState *newState)
{
	StateManager::getSingletonPtr()->changeState(newState);
}

void BaseState::pushState(BaseState *newState)
{
	StateManager::getSingletonPtr()->pushState(newState);
}

void BaseState::popState()
{
	StateManager::getSingletonPtr()->popState();
}

bool BaseState::keyPressed(const OIS::KeyEvent&evt)
{
	return true;
}

bool BaseState::keyReleased(const OIS::KeyEvent&evt)
{
	return true;
}

bool BaseState::mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id)
{
		MyGUIManager::getSingletonPtr()->injectMouseButtonDown(MyGUIManager::convertButton(id));
		
		return true;
}

bool BaseState::mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id)
{
		MyGUIManager::getSingletonPtr()->injectMouseButtonUp(MyGUIManager::convertButton(id));
		
		return true;
	
}

bool BaseState::mouseMoved(const OIS::MouseEvent&evt)
{
	OIS::MouseState state = evt.state;
	MyGUIManager::getSingletonPtr()->injectMouseMove(state.X.rel, state.Y.rel);

	return true;
}