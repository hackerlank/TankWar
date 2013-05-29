#include "CreditGUIState.h"
#include "../GUI/MyGUIManager.h"
#include "PlayingState.h"
#include "StateManager.h"
#include "MainMenuState.h"

CreditGUIState::CreditGUIState()
	: m_pSceneMgr(NULL),
	m_pRenderWindow(NULL),
	m_pCamera(NULL),
	m_pViewport(NULL)

{
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("intro2","intro2.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("help","help.png");
}

void CreditGUIState::Init()
{
	m_pSceneMgr=NULL;
	m_pRenderWindow=NULL;
	m_pCamera=NULL;
	m_pViewport=NULL;
}
CreditGUIState::~CreditGUIState()
{

}

void CreditGUIState::enter()
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getAideSceneMgr();
	m_pRenderWindow	= GameApp::getSingletonPtr()->getRenderWindow();


	CameraInit();

	//����GUI�¼���;
	createGUIEvent();
}

void CreditGUIState::exit()
{
	
	/*if (MyGUIManager::getSingletonPtr()->destroyWindow())
	{*/
		m_pSceneMgr->destroyAllCameras();
		m_pRenderWindow->removeAllViewports();
		MyGUIManager::getSingletonPtr()->destroyWindow("CreditGUI");
	/*}*/
	
	//m_pSceneMgr->destroyAllLights();
}

void CreditGUIState::update(float timeSinceLastFrame)
{
	
}

void CreditGUIState::CameraInit()
{
	//�����������е����;
	m_pSceneMgr->destroyAllCameras();
	////�Ƴ��������е��ӿ�;
	m_pRenderWindow->removeAllViewports();

	m_pCamera = m_pSceneMgr->createCamera("CreditGUI");
	m_pViewport = m_pRenderWindow->addViewport(m_pCamera);

	//��������󶨵�look�ڵ�

}


void CreditGUIState::createGUIEvent()
{

	MyGUIManager::getSingletonPtr()->loadWindow("CreditGUI");
	/*CEGUI::ImagesetManager::getSingleton().createFromImageFile("intro2","intro2.png");*/
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Image2")->setProperty("Image",
		"set:intro2 image:full_image");
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Image4")->setProperty("Image",
		"set:help image:full_image");

	MyGUIManager::getSingletonPtr()->subscribeEvent("back",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&CreditGUIState::Back, this));

}

bool CreditGUIState::Back(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(MainMenuState::getSingletonPtr());
	return true;
}