/*
 * MainMenuState.cpp
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#include "MainmenuState.h"
#include "../GUI/MyGUIManager.h"
#include "PlayingState.h"
#include "StateManager.h"
#include "MultiplayerGUIState.h"
#include "CreditGUIState.h"
#include "OptionGUIState.h"
#include "AboutGUIState.h"
#include "../Audio/AudioSystem.h"

MainMenuState::MainMenuState()
	: m_pSceneMgr(NULL),
	m_pRenderWindow(NULL),
	m_pCamera(NULL),
	m_pViewport(NULL)
	
{
	//加载背景图片;
}
void MainMenuState::Init()
{
	m_pSceneMgr=NULL;
	m_pRenderWindow=NULL;
	m_pCamera=NULL;
	m_pViewport=NULL;
}
MainMenuState::~MainMenuState()
{

}

void MainMenuState::enter()
{
	//开始播放背景音乐;
	AudioSystem::GetSingletonPtr()->play(MENU_BACKGROUND, 10, true);

	m_pSceneMgr = GameApp::getSingletonPtr()->getAideSceneMgr();
	m_pRenderWindow	= GameApp::getSingletonPtr()->getRenderWindow();

	MyGUIManager::getSingletonPtr()->loadWindow("MainGUI");
	//加载背景图片;
	//CEGUI::ImagesetManager::getSingleton().createFromImageFile("welcome","welcome.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("welcome","welcome.png");
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Image")->setProperty("Image",
		"set:welcome image:full_image");

	CameraInit();

	//创建GUI事件绑定;
	createGUIEvent();
}

void MainMenuState::exit()
{
	
	/*if (MyGUIManager::getSingletonPtr()->destroyWindow())
	{*/
		m_pSceneMgr->destroyAllCameras();
		m_pRenderWindow->removeAllViewports();
		MyGUIManager::getSingletonPtr()->destroyWindow("MainGUI");
	/*}*/
	
	//m_pSceneMgr->destroyAllLights();
}

void MainMenuState::update(float timeSinceLastFrame)
{
	
}

void MainMenuState::CameraInit()
{
	//首先销毁已有的相机;
	m_pSceneMgr->destroyAllCameras();
	////移除所有已有的视口;
	m_pRenderWindow->removeAllViewports();

	m_pCamera = m_pSceneMgr->createCamera("MainMenuCam");
	m_pViewport = m_pRenderWindow->addViewport(m_pCamera);

	//将摄像机绑定到look节点;
}


void MainMenuState::createGUIEvent()
{
	MyGUIManager::getSingletonPtr()->subscribeEvent("Multiplay",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MainMenuState::Play, this));

	MyGUIManager::getSingletonPtr()->subscribeEvent("Options",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MainMenuState::Option, this));

	MyGUIManager::getSingletonPtr()->subscribeEvent("Credit",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MainMenuState::Show, this));

	MyGUIManager::getSingletonPtr()->subscribeEvent("About",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MainMenuState::About, this));

	MyGUIManager::getSingletonPtr()->subscribeEvent("Exit",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MainMenuState::onExit, this));

}

bool MainMenuState::onExit(const CEGUI::EventArgs& evt)
{
	GameApp::getSingletonPtr()->shutdown();
	return true;
}

bool MainMenuState::Play(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(MultiplayerGUIState::getSingletonPtr());
	return true;
}

bool MainMenuState::Option(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(OptionGUIState::getSingletonPtr());
	return true;
}

bool MainMenuState::About(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(AboutGUIState::getSingletonPtr());
	return true;
}

bool MainMenuState::Show(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(CreditGUIState::getSingletonPtr());
	return true;
}