#include "MultiplayerGUIState.h"
#include "../GUI/MyGUIManager.h"
#include "PlayingState.h"
#include "StateManager.h"
#include "MainMenuState.h"
#include "ChooseMapState.h"
#include "../Audio/AudioSystem.h"



MultiplayerGUIState::MultiplayerGUIState()
	: m_pSceneMgr(NULL),
	m_pRenderWindow(NULL),
	m_pCamera(NULL),
	m_pViewport(NULL)
	
{
	
}
void MultiplayerGUIState::Init()
{
	m_pSceneMgr=NULL;
	m_pRenderWindow=NULL;
	m_pCamera=NULL;
	m_pViewport=NULL;
}
MultiplayerGUIState::~MultiplayerGUIState()
{

}

void MultiplayerGUIState::enter()
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getAideSceneMgr();
	m_pRenderWindow	= GameApp::getSingletonPtr()->getRenderWindow();


	CameraInit();

	//创建GUI事件绑定;
	createGUIEvent();
	initServerInfoList();
}

void MultiplayerGUIState::exit()
{
	
	/*if (MyGUIManager::getSingletonPtr()->destroyWindow())
	{*/
	m_pSceneMgr->destroyAllCameras();
	m_pRenderWindow->removeAllViewports();
	MyGUIManager::getSingletonPtr()->destroyWindow("SearchServer");
	/*}*/
	
	//m_pSceneMgr->destroyAllLights();
}

void MultiplayerGUIState::update(float timeSinceLastFrame)
{

}

void MultiplayerGUIState::CameraInit()
{
	//首先销毁已有的相机;
	m_pSceneMgr->destroyAllCameras();
	////移除所有已有的视口;
	m_pRenderWindow->removeAllViewports();

	m_pCamera = m_pSceneMgr->createCamera("SearchServer");
	m_pViewport = m_pRenderWindow->addViewport(m_pCamera);

	//将摄像机绑定到look节点

}


void MultiplayerGUIState::createGUIEvent()
{
	MyGUIManager::getSingletonPtr()->loadWindow("SearchServer");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("intro3","intro3.png");
	CEGUI::WindowManager::getSingletonPtr()->getWindow("SearchServer")->setProperty("Image",
		"set:intro3 image:full_image");

	MyGUIManager::getSingletonPtr()->subscribeEvent("SearchServer/Create",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MultiplayerGUIState::Create, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("SearchServer/Join",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MultiplayerGUIState::Join, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("SearchServer/Search",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MultiplayerGUIState::Search, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("SearchServer/Back",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MultiplayerGUIState::Back, this));
	MyGUIManager::getSingletonPtr()->subscribeEvent("SearchServer/ServersInfo",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&MultiplayerGUIState::SelectChange, this));

}

bool MultiplayerGUIState::Create(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(ChooseMapState::getSingletonPtr());
	return true;
}


//作为客户机进入游戏
bool MultiplayerGUIState::Join(const CEGUI::EventArgs& evt)
{
	//关闭背景音乐;
	AudioSystem::GetSingletonPtr()->stop(MENU_BACKGROUND);

	StateManager::getSingletonPtr()->changeState(PlayingState::getSingletonPtr());
	return true;
}

bool MultiplayerGUIState::Search(const CEGUI::EventArgs& evt)
{
	CEGUI::MultiColumnList* pkList = (CEGUI::MultiColumnList* )CEGUI::WindowManager::getSingleton().getWindow("SearchServer/ServersInfo");
	CEGUI::ListboxItem *listboxitem;
	//add Server Name
	listboxitem = new CEGUI::ListboxTextItem("name");
	listboxitem->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
	listboxitem->setSelectionColours(CEGUI::colour(0.027f,0.525f,0.666f,0.7f));
	//row = pkList->addRow(listboxitem, 0);

// 	//add IP addrress
// 	listboxitem = new CEGUI::ListboxTextItem(ip.c_str());
// 	listboxitem->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
// 	listboxitem->setSelectionColours(CEGUI::colour(0.027f,0.525f,0.666f,0.7f));
// 	pkList->setItem(listboxitem, 1, row); 
// 
// 	//add Ping Value
// 	std::string strping;
// 	strping=Ogre::StringConverter::toString(pingvalue)+"ms";
// 	listboxitem = new CEGUI::ListboxTextItem(strping.c_str());
// 	listboxitem->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
// 	listboxitem->setSelectionColours(CEGUI::colour(0.027f,0.525f,0.666f,0.7f));
// 	pkList->setItem(listboxitem, 2, row); 
// 
// 	pkList->setItemSelectState(listboxitem,true);
	return true;
}

bool MultiplayerGUIState::Back(const CEGUI::EventArgs& evt)
{
	StateManager::getSingletonPtr()->changeState(MainMenuState::getSingletonPtr());
	return true;
}

bool MultiplayerGUIState::SelectChange(const CEGUI::EventArgs& evt)
{
// 	const CEGUI::WindowEventArgs& windowEventArgs = static_cast<const CEGUI::WindowEventArgs&>(e);
// 
// 	CEGUI::MultiColumnList* pkList = static_cast<CEGUI::MultiColumnList*>(windowEventArgs.window);
// 
// 	CEGUI::uint i;
// 	for(i=0;i<pkList->getRowCount();i++)
// 	{
// 		if(pkList->isItemSelected(CEGUI::MCLGridRef(i,0)))
// 		{
// 			this->mCurrentChoosedServer = this->mServerInfoList[i];
// 			break;
// 		}
// 	}

	return true;
}

void MultiplayerGUIState::initServerInfoList(void)
{

	CEGUI::MultiColumnList* pkList = (CEGUI::MultiColumnList* )CEGUI::WindowManager::getSingleton().getWindow("SearchServer/ServersInfo");
	pkList->addColumn("Server name", 0, CEGUI::UDim(0.5f,0.f));
	pkList->addColumn("IP", 1,  CEGUI::UDim(0.3f,0.f));
	pkList->addColumn("Ping", 2,  CEGUI::UDim(0.2f,0.f));
	pkList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
	pkList->setUserSortControlEnabled(false);

}

