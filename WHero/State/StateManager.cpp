/*
 * StateManager.cpp
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#include "StateManager.h"

StateManager::StateManager()
{

}

StateManager::~StateManager()
{

}

void StateManager::destroy()
{
	while(!m_StateStack.empty())
	{
		m_StateStack.pop_back();
	}
	m_StateStack.clear();
}

void StateManager::changeState(BaseState*newState)
{
	//µ¯³öÕ»¶¥×´Ì¬;
	if(!m_StateStack.empty())
	{
		m_StateStack.back()->exit();
		m_StateStack.pop_back();
	}
	m_StateStack.push_back(newState);
	newState->enter();
}

void StateManager::pushState(BaseState*newState)
{
	//Ôİ¶¨Õ»¶¥×´Ì¬;
	if(!m_StateStack.empty())
		m_StateStack.back()->pause();

	m_StateStack.push_back(newState);
	newState->enter();
}

void StateManager::popState()
{
	//µ¯³öÕ»¶¥×´Ì¬;
	if(!m_StateStack.empty())
	{
		m_StateStack.back()->exit();
		m_StateStack.pop_back();
	}

	//Èç¹ûÓĞÉÏÒ»¸ö×´Ì¬£¬Ôò»Ö¸´Ëü;
	if(!m_StateStack.empty())
		m_StateStack.back()->resume();
}