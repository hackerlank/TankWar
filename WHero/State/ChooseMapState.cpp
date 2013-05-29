#include "ChooseMapState.h"
#include "../GUI/MyGUIManager.h"
#include "PlayingState.h"
#include "StateManager.h"
#include "MultiplayerGUIState.h"

ChooseMapState::ChooseMapState()
	: m_pSceneMgr(NULL),
	m_pRenderWindow(NULL),
	m_pCamera(NULL),
	m_pViewport(NULL)
{
	mMapIndex=1;
}
void ChooseMapState::Init()
{
	m_pSceneMgr=NULL;
	m_pRenderWindow=NULL;
	m_pCamera=NULL;
	m_pViewport=NULL;
}
ChooseMapState::~ChooseMapState()
{

}

void ChooseMapState::enter()
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getAideSceneMgr();
	m_pRenderWindow	= GameApp::getSingletonPtr()->getRenderWindow();


	CameraInit();

	//创建GUI事件绑定;
	createGUIEvent();
	ChooseMapState::getSingletonPtr()->SetMap(mMapIndex);
}

void ChooseMapState::exit()
{
	
	/*if (MyGUIManager::getSingletonPtr()->destroyWindow())
	{*/
		m_pSceneMgr->destroyAllCameras();
		m_pRenderWindow->removeAllViewports();
		MyGUIManager::getSingletonPtr()->destroyWindow("ChooseMap");
	/*}*/
	
	//m_pSceneMgr->destroyAllLights();
}
void ChooseMapState::update(float timeSinceLastFrame)
{

}

void ChooseMapState::CameraInit()
{
	//首先销毁已有的相机;
	m_pSceneMgr->destroyAllCameras();
	////移除所有已有的视口;
	m_pRenderWindow->removeAllViewports();

	m_pCamera = m_pSceneMgr->createCamera("ChooseMap");
	m_pViewport = m_pRenderWindow->addViewport(m_pCamera);

	//将摄像机绑定到look节点

}

void ChooseMapState::createGUIEvent()
{

	MyGUIManager::getSingletonPtr()->loadWindow("ChooseMap");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("intro1","intro1.png");
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Image3")->setProperty("Image",
		"set:intro1 image:full_image");

	// 	MyGUIManager::getSingletonPtr()->subscribeEvent("Edit",
	// 		CEGUI::PushButton::EventClicked, 
	// 		CEGUI::Event::Subscriber(&OptionGUIState::Edit, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("Next",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&ChooseMapState::handleNext, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("Back",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&ChooseMapState::handleBack, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("Right",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&ChooseMapState::handleRight, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("Left",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&ChooseMapState::handleLeft, this));
}
//创建主机后，进入游戏
bool ChooseMapState::handleNext(const CEGUI::EventArgs& e)
{
	StateManager::getSingletonPtr()->changeState(PlayingState::getSingletonPtr());
	return true;
}

bool ChooseMapState::handleBack(const CEGUI::EventArgs& e)
{
	StateManager::getSingletonPtr()->changeState(MultiplayerGUIState::getSingletonPtr());
	return true;
}

bool ChooseMapState::handleRight(const CEGUI::EventArgs& e)
{
	//MyAudioSystem::GetSingletonPtr()->myaudio.Update(MyAudioSystem::button,MyAudioSystem::buttonClick);
	mMapIndex++;
	if(mMapIndex==5)
		mMapIndex=1;

	ChooseMapState::getSingletonPtr()->SetMap(mMapIndex);

	return true;

}

bool ChooseMapState::handleLeft(const CEGUI::EventArgs& e)
{
	//MyAudioSystem::GetSingletonPtr()->myaudio.Update(MyAudioSystem::button,MyAudioSystem::buttonClick);
	mMapIndex--;
	if(mMapIndex==0)
		mMapIndex=4;

	ChooseMapState::getSingletonPtr()->SetMap(mMapIndex);

	return true;

}

void ChooseMapState::SetMap(int mapindex)
{
	std::string strsetvalue;
	strsetvalue="set:"+Ogre::StringConverter::toString(mapindex)+" image:full_image";
	CEGUI::ImagesetManager::getSingleton().createFromImageFile(Ogre::StringConverter::toString(mapindex),Ogre::StringConverter::toString(mapindex)+".jpg");
	CEGUI::WindowManager::getSingletonPtr()->getWindow("Map")->setProperty("Image",
		strsetvalue.c_str());
}