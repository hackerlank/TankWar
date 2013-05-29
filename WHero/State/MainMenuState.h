/*
 * MainMenuState.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "../State/BaseState.h"
#include "../Common/SingletonT.h"
#include "../GameApp.h"

class MainMenuState :public BaseState ,public SingletonT<MainMenuState>
{
	SINGLETON_DEFINE(MainMenuState)
public:
	MainMenuState();
	~MainMenuState();
	
	virtual void enter(void);
	virtual void exit(void);

	virtual void pause(void){}
	virtual void resume(void){}

	virtual void update(float timeSinceLastFrame);
	void	Init();
protected:
	void CameraInit();


	//绑定事件;
	void createGUIEvent();
	bool onExit(const CEGUI::EventArgs& evt);
	bool Play(const CEGUI::EventArgs& evt);
	bool Option(const CEGUI::EventArgs& evt);
	bool Show(const CEGUI::EventArgs& evt);
	bool About(const CEGUI::EventArgs& evt);

private:
	/*Ogre::RenderWindow		*m_pRenderWindow;*/
	Ogre::SceneManager		*m_pSceneMgr;
	Ogre::RenderWindow		*m_pRenderWindow;


	Ogre::Camera			*m_pCamera;
	Ogre::Viewport			*m_pViewport;

	bool					m_pInit;	//是否已经初始化，保证只初始化一次;*/

};
#endif