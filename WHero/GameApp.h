/*
 * TankWar.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#ifndef TANKWAR_H_
#define TANKWAR_H_

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OIS.h>
#include "OgreException.h"
#include "../GUI/MyGUIManager.h"

class StateManager;
class BaseState;

class GameApp :public Ogre::Singleton<GameApp>, OIS::KeyListener, OIS::MouseListener
{
	SINGLETON_DEFINE(GameApp)
public:
	GameApp();
	~GameApp();

	void	StartGame();

	//�����˳�;
	inline void	shutdown(){ m_bShutdown = true; }

	//��ȡ��Ϸ������������״̬ʹ��;
	inline	Ogre::SceneManager	*getGameSceneMgr(){ return m_pGameSceneMgr; }

	//�������������������������ã���menu;
	inline	Ogre::SceneManager	*getAideSceneMgr(){ return m_pAideSceneMgr; }

	//��ȡOgre����Ⱦ����;
	inline	Ogre::RenderWindow	*getRenderWindow(){ return m_pRenderWnd; }

protected:
	bool	Setup(/*Ogre::String name*/);

	bool	Configure();

	bool	SetupResources();

	void	SceneMgrInit();

	//��ʼ���������;
	void	OISInit();

	//ʼ��״̬������;
	void    StateInit();

	//��ʼ��GUI;
	void    GUIInit();

	void	Update(float timeSinceLastFrame);

	//�ͷ���Դ;
	void	Release();

protected:
	bool    keyPressed(const OIS::KeyEvent& evt);
	bool	keyReleased(const OIS::KeyEvent& evt);

	bool	mouseMoved(const OIS::MouseEvent& evt);
	bool	mousePressed(const OIS::MouseEvent&evt,OIS::MouseButtonID id);
	bool	mouseReleased(const OIS::MouseEvent&evt,OIS::MouseButtonID id);

public:
	Ogre::Root				*m_pRoot;
	Ogre::RenderWindow		*m_pRenderWnd;

	//Ҫ�õ��ĳ�����������AideSceneMgr��������Ĺ���ȸ�����;
	Ogre::SceneManager		*m_pGameSceneMgr;
	Ogre::SceneManager		*m_pAideSceneMgr;

	//OGRE��־��ʱ��;
	Ogre::Log*				m_pLog;
	Ogre::Timer*			m_pTimer;

	//Ҫ��InputMgr�滻;
	OIS::InputManager		*m_pInputMgr;
	OIS::Keyboard			*m_pKeyboard;
	OIS::Mouse				*m_pMouse;

	//���ֹ�����;
//	StateManager			*m_pStateMgr;
	MyGUIManager			*m_pGUIMgr;

	//�����Ƿ�ɽ���;
	bool					m_bShutdown;
};
#endif//
