/*
 * TankWar.cpp
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#include "GameApp.h"
#include "../State/StateManager.h"
#include "../State/MainMenuState.h"
#include "../State/PlayingState.h"

template<> GameApp* Ogre::Singleton<GameApp>::ms_Singleton = NULL;

GameApp::GameApp()
	:m_pRoot(NULL),
	m_pGameSceneMgr(NULL),
	m_pAideSceneMgr(NULL),
	m_pRenderWnd(NULL),
	m_pLog(NULL),
	m_pTimer(NULL),
	m_pInputMgr(NULL),
	m_pKeyboard(NULL),
	m_pMouse(NULL),
	m_bShutdown(false)
	//m_pGUIMgr(NULL)
{
	//m_pStateMgr = new StateManager();
}

GameApp::~GameApp()
{

}

void GameApp::StartGame()
{
	if (!Setup())
	{
		return;
	}

	float timeSinceLastFrame = 1.0;
	float startTime = 0.0;

	//游戏循环
	while (!m_bShutdown)
	{
		if (m_pRenderWnd->isClosed())
			m_bShutdown = true;

		Ogre::WindowEventUtilities::messagePump();

		if (true/*m_pRenderWnd->isActive()*/)
		{
			startTime = m_pTimer->getMillisecondsCPU();

			m_pKeyboard->capture();
			m_pMouse->capture();

			Update(timeSinceLastFrame);

			//渲染Ogre
			m_pRoot->renderOneFrame();

			timeSinceLastFrame = m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
			Sleep(1000);
		}

		m_pLog->logMessage("Main loop quit");
	}

	//释放资源;
	Release();
	
}

bool GameApp::Setup()
{
	//OGRE日志;
	Ogre::LogManager* logMgr = new Ogre::LogManager();
	m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);

	m_pRoot = new Ogre::Root("plugins_d.cfg");

	//配置;
	if (!Configure())
		return false;

	//设置资源加载;
	SetupResources();

	//场景管理器的初始化;
	SceneMgrInit();

	//输入输出初始化;
	OISInit();

	//GUI管理器的初始化;
	GUIInit();

	//状态管理器的初始化;
	StateInit();

	m_pTimer = new Ogre::Timer();
	m_pTimer->reset();

	m_pRenderWnd->setActive(true);

	return true;
}

bool GameApp::Configure()
{
	//显示配置窗口;
	if (!m_pRoot->showConfigDialog())
	{
		//Release();
		return false;
	}

	//初始化渲染窗口;
	m_pRenderWnd = m_pRoot->initialise(true, "WHero");
	return true;
}

bool GameApp::SetupResources()
{
	// load resources
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
	cf.load("resources_d.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	return true;
}

void GameApp::SceneMgrInit()
{
	m_pAideSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "AideSceneMgr");
	m_pGameSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "SceneMgr");

	m_pGameSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
}

void GameApp::StateInit()
{
	BaseState *baseState=MainMenuState::getSingletonPtr();
	if (NULL!=baseState)
	{
		StateManager::getSingletonPtr()->pushState(baseState);
	}
	
}

void GameApp::GUIInit()
{
	//初始化GUI
	m_pGUIMgr = MyGUIManager::getSingletonPtr();
	m_pGUIMgr->init();
	
}

void GameApp::OISInit()
{
	size_t hWnd = 0;
	OIS::ParamList paramList;
	m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);

	paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

	m_pInputMgr = OIS::InputManager::createInputSystem(paramList);

	m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
	m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));

	m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
	m_pMouse->getMouseState().width = m_pRenderWnd->getWidth();

	//设置键盘和鼠标的回调;
	m_pMouse->setEventCallback(this);
	m_pKeyboard->setEventCallback(this);
}

void GameApp::Update(float timeSinceLastFrame)
{
	if(!StateManager::getSingletonPtr()->empty())
	{
		StateManager::getSingletonPtr()->update(timeSinceLastFrame);
	}

	//渲染GUI;
	if (m_pGUIMgr!=NULL)
	{
		m_pGUIMgr->update(timeSinceLastFrame);
	}
}

void GameApp::Release()
{
	//释放各种管理器资源
	StateManager::getSingletonPtr()->destroy();
	//m_pGUIMgr->destroy();

	//清除OIS;
	if (m_pInputMgr)
	{
		m_pInputMgr->destroyInputObject(m_pMouse);
		m_pInputMgr->destroyInputObject(m_pKeyboard);
		OIS::InputManager::destroyInputSystem(m_pInputMgr);
		m_pInputMgr = 0;
	}

	//清除场景;
	m_pGameSceneMgr->clearScene();
	m_pAideSceneMgr->clearScene();

	m_pRoot->destroySceneManager(m_pGameSceneMgr);
	m_pRoot->destroySceneManager(m_pAideSceneMgr);

	m_pRenderWnd->destroy();
	m_pRoot->shutdown();
}

bool GameApp::keyPressed(const OIS::KeyEvent& evt)
{
	return StateManager::getSingletonPtr()->keyPressed(evt);
}

bool GameApp::keyReleased(const OIS::KeyEvent& evt)
{
	return StateManager::getSingletonPtr()->keyReleased(evt);
}

bool GameApp::mousePressed(const OIS::MouseEvent&evt,OIS::MouseButtonID id)
{
	//检测鼠标边际;

	return StateManager::getSingletonPtr()->mousePressed(evt, id);
}

bool GameApp::mouseMoved(const OIS::MouseEvent& evt)
{
	//检测鼠标的边界;

	//时时更新鼠标的位置;

	return StateManager::getSingletonPtr()->mouseMoved(evt);
}

bool GameApp::mouseReleased(const OIS::MouseEvent&evt,OIS::MouseButtonID id)
{
	//检测鼠标边际;

	return StateManager::getSingletonPtr()->mouseReleased(evt, id);
}