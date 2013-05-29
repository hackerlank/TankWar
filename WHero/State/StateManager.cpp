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
	//����ջ��״̬;
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
	//�ݶ�ջ��״̬;
	if(!m_StateStack.empty())
		m_StateStack.back()->pause();

	m_StateStack.push_back(newState);
	newState->enter();
}

void StateManager::popState()
{
	//����ջ��״̬;
	if(!m_StateStack.empty())
	{
		m_StateStack.back()->exit();
		m_StateStack.pop_back();
	}

	//�������һ��״̬����ָ���;
	if(!m_StateStack.empty())
		m_StateStack.back()->resume();
}