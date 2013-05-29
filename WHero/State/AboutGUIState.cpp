#include "AboutGUIState.h"
#include "../GUI/MyGUIManager.h"
#include "PlayingState.h"
#include "StateManager.h"
#include "MainMenuState.h"

AboutGUIState::AboutGUIState()
	: m_pSceneMgr(NULL),
	m_pRenderWindow(NULL),
	m_pCamera(NULL),
	m_pViewport(NULL)

{
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("intro2","intro2.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("info","info.png");
}

void AboutGUIState::Init()
{
	m_pSceneMgr=NULL;
	m_pRenderWindow=NULL;
	m_pCamera=NULL;
	m_pViewport=NULL;
}
AboutGUIState::~AboutGUIState()
{

}

void AboutGUIState::enter()
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getAideSceneMgr();
	m_pRenderWindow	= GameApp::getSingletonPtr()->getRenderWindow();


	CameraInit();

	//创建GUI事件绑定;
	createGUIEvent();
}

void AboutGUIState::exit()
{
	
	/*if (MyGUIManager::getSingletonPtr()->destroyWindow())
	{*/
		m_pSceneMgr->destroyAllCameras();
		m_pRenderWindow->removeAllViewports();
		MyGUIManager::getSingletonPtr()->destroyWindow("About");
	/*}*/
	
	//m_pSceneMgr->destroyAllLights();
}

void AboutGUIState::update(float timeSinceLastFrame)
{
	
}

void AboutGUIState::CameraInit()
{
	//首先销毁已有的相机;
	m_pSceneMgr->destroyAllCameras();
	////移除所有已有的视口;
	m_pRenderWindow->removeAllViewports();

	m_pCamera = m_pSceneMgr->createCamera("About");
	m_pViewport = m_pRenderWindow->addViewport(m_pCamera);

	//将摄像机绑定到look节点

}


void AboutGUIState::createGUIEvent()
{

	MyGUIManager::getSingletonPtr()->loadWindow("About");
	/*CEGUI::ImagesetManager::getSingleton().createFromImageFile("intro2","intro2.png");*/
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Image2")->setProperty("Image",
		"set:intro2 image:full_image");
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Image4")->setProperty("Image",
		"set:info image:full_image");

	MyGUIManager::getSingletonPtr()->subscribeEvent("back",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&AboutGUIState::Back, this));

}

bool AboutGUIState::Back(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(MainMenuState::getSingletonPtr());
	return true;
}