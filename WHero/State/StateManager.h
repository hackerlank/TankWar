/*
 * StateManager.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#ifndef  STATEMANAGER_H_
#define  STATEMANAGER_H_

#include "vector"
#include "../State/BaseState.h"
#include "../Common/SingletonT.h"

class StateManager : public BaseState, public SingletonT<StateManager>
{
	SINGLETON_DEFINE(StateManager)

public:
	virtual ~StateManager();

	virtual void enter(){}
	virtual void exit(){}

	void	destroy();

	//È¡µÃÕ»¶¥×´Ì¬
	BaseState* stateTop()
	{
		assert(!m_StateStack.empty() 
			&& "State stack is empty");
		return m_StateStack.back();
	}

	bool empty() const{return m_StateStack.empty();}
	int size() const{return (int)m_StateStack.size();}

	void changeState(BaseState*newState);
	void pushState(BaseState*newState);
	void popState();

	virtual void update(float timeSinceLastFrame){stateTop()->update(timeSinceLastFrame); }

public:
	inline bool keyPressed(const OIS::KeyEvent&evt){ return stateTop()->keyPressed(evt); }
	inline bool keyReleased(const OIS::KeyEvent&evt){ return stateTop()->keyReleased(evt); }

	inline bool mouseMoved(const OIS::MouseEvent&evt){ return stateTop()->mouseMoved(evt); }
	inline bool mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id) { return stateTop()->mousePressed(evt,id); }
	inline bool mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id) { return stateTop()->mouseReleased(evt, id); }

private:
	StateManager();
	void Init(BaseState*state);

private:
	std::vector<BaseState*>		m_StateStack;
};
#endif