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

	//设置退出;
	inline void	shutdown(){ m_bShutdown = true; }

	//获取游戏场景管理器，状态使用;
	inline	Ogre::SceneManager	*getGameSceneMgr(){ return m_pGameSceneMgr; }

	//其他辅助场景管理器，辅助用，如menu;
	inline	Ogre::SceneManager	*getAideSceneMgr(){ return m_pAideSceneMgr; }

	//获取Ogre主渲染窗口;
	inline	Ogre::RenderWindow	*getRenderWindow(){ return m_pRenderWnd; }

protected:
	bool	Setup(/*Ogre::String name*/);

	bool	Configure();

	bool	SetupResources();

	void	SceneMgrInit();

	//初始化输入输出;
	void	OISInit();

	//始化状态管理器;
	void    StateInit();

	//初始化GUI;
	void    GUIInit();

	void	Update(float timeSinceLastFrame);

	//释放资源;
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

	//要用到的场景管理器，AideSceneMgr用作界面的管理等辅助用;
	Ogre::SceneManager		*m_pGameSceneMgr;
	Ogre::SceneManager		*m_pAideSceneMgr;

	//OGRE日志和时间;
	Ogre::Log*				m_pLog;
	Ogre::Timer*			m_pTimer;

	//要被InputMgr替换;
	OIS::InputManager		*m_pInputMgr;
	OIS::Keyboard			*m_pKeyboard;
	OIS::Mouse				*m_pMouse;

	//各种管理器;
//	StateManager			*m_pStateMgr;
	MyGUIManager			*m_pGUIMgr;

	//程序是否可结束;
	bool					m_bShutdown;
};
#endif//
