#include "OptionGUIState.h"
#include "../GUI/MyGUIManager.h"
#include "PlayingState.h"
#include "StateManager.h"
#include "MainMenuState.h"

OptionGUIState::OptionGUIState()
	: m_pSceneMgr(NULL),
	m_pRenderWindow(NULL),
	m_pCamera(NULL),
	m_pViewport(NULL)
{
}
void OptionGUIState::Init()
{
	m_pSceneMgr=NULL;
	m_pRenderWindow=NULL;
	m_pCamera=NULL;
	m_pViewport=NULL;
}
OptionGUIState::~OptionGUIState()
{

}

void OptionGUIState::enter()
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getAideSceneMgr();
	m_pRenderWindow	= GameApp::getSingletonPtr()->getRenderWindow();


	CameraInit();

	//����GUI�¼���;
	createGUIEvent();
}

void OptionGUIState::exit()
{
	
	/*if (MyGUIManager::getSingletonPtr()->destroyWindow())
	{*/
		m_pSceneMgr->destroyAllCameras();
		m_pRenderWindow->removeAllViewports();
		MyGUIManager::getSingletonPtr()->destroyWindow("Options");
	/*}*/
	
	//m_pSceneMgr->destroyAllLights();
}

void OptionGUIState::update(float timeSinceLastFrame)
{
	
}

void OptionGUIState::CameraInit()
{
	//�����������е����;
	m_pSceneMgr->destroyAllCameras();
	////�Ƴ��������е��ӿ�;
	m_pRenderWindow->removeAllViewports();

	m_pCamera = m_pSceneMgr->createCamera("Options");
	m_pViewport = m_pRenderWindow->addViewport(m_pCamera);

	//��������󶨵�look�ڵ�

}

void OptionGUIState::createGUIEvent()
{

	MyGUIManager::getSingletonPtr()->loadWindow("Options");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("intro2","intro2.png");
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Image1")->setProperty("Image",
		"set:intro2 image:full_image");

// 	MyGUIManager::getSingletonPtr()->subscribeEvent("Edit",
// 		CEGUI::PushButton::EventClicked, 
// 		CEGUI::Event::Subscriber(&OptionGUIState::Edit, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("Screen",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&OptionGUIState::IsFullScreen, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("VoiceB",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&OptionGUIState::Voice, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("back",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&OptionGUIState::Back, this));

}

// bool OptionGUIState::Edit(const CEGUI::EventArgs& evt)
// {
// 	CEGUI::Editbox *nameEditbox = (CEGUI::Editbox*)windowMgr->getWindow("Edit");
// 	nameEditbox->setText( );
// 
// }

bool OptionGUIState::IsFullScreen(const CEGUI::EventArgs& evt)
{
	std::string state;
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	state = wmgr.getWindow(CEGUI::String("Screen"))->getText().c_str();

	if (state == "No")
	{
		state = "Yes";
		//MyClientNetworkSystem::GetSingleton().NotifyPlayerStateChange("UnReady");
	}
	else if (state == "Yes")
	{
		state = "No";
		//MyClientNetworkSystem::GetSingleton().NotifyPlayerStateChange("Ready");

	}

	wmgr.getWindow(CEGUI::String("Screen"))->setText(state.c_str());


	return true;
}

bool OptionGUIState::Voice(const CEGUI::EventArgs& evt)
{
	//MyAudioSystem::GetSingletonPtr()->myaudio.Update(MyAudioSystem::button,MyAudioSystem::buttonClick);
	std::string state;
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	state = wmgr.getWindow(CEGUI::String("VoiceB"))->getText().c_str();

	if (state == "Yes")
	{
		state = "No";
		//MyClientNetworkSystem::GetSingleton().NotifyPlayerStateChange("UnReady");
	}
	else if (state == "No")
	{
		state = "Yes";
		//MyClientNetworkSystem::GetSingleton().NotifyPlayerStateChange("Ready");

	}

	wmgr.getWindow(CEGUI::String("VoiceB"))->setText(state.c_str());

	return true;
}

bool OptionGUIState::Back(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(MainMenuState::getSingletonPtr());
	return true;
}