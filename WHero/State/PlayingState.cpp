/*
 * PlayingState.cpp
 *
 *  Created on: June 23, 2012
 *      Author: hongxiaoqiang
 */
#include "PlayingState.h"
#include "StateManager.h"
#include "MainMenuState.h"
#include "../Objects/Tank/M60.h"
#include "../Objects/Tank/T46.h"
#include "../GUI/MyGUIManager.h"
#include "../Audio/AudioSystem.h"
#include "../Objects/Bullet/BulletManager.h"
#include "../3rd/DotsceneLoader/DotSceneLoader.h"
#include "../NetWork/MyGameCommand.h"
#include "../NetWork/CommonNetWorkProtocal.h"
#include "../NetWork/MyClientNetworkSystem.h"
#include "../NetWork/MyServerNetworkSystem.h"
#include "../NetWork/MyGameCommand.h"

PlayingState::PlayingState(void)
	:m_pRoot(NULL),
	m_pSceneMgr(NULL),
	m_pRenderWnd(NULL),
	/*m_pLookAtNode(NULL),*/
	m_pCamera(NULL),
	m_pViewport(NULL),
	m_pLog(NULL),
	tank_m60(NULL),
	m_pMapEntity(NULL),
	m_pMapNode(NULL),
	m_isShowExit(false)
{
}

PlayingState::~PlayingState(void)
{
}

void PlayingState::enter()
{
	//�������;
	MyGUIManager::getSingletonPtr()->showGUICursor(false);

	//Ogre��־;
	GameApp::getSingletonPtr()->m_pLog->logMessage("Entering PlayingState.h.");

	/*m_pSceneMgr = GameApp::getSingletonPtr()->m_pRoot->createSceneManager(1, "GameSceneMgr");*/
	m_pSceneMgr	= GameApp::getSingletonPtr()->getGameSceneMgr();
	m_pRenderWnd= GameApp::getSingletonPtr()->getRenderWindow();

	createScene();
	createLight();
	createCamera();
	createUI();
	createUIEvent();
	createNetWork();

	//���ű�������;
	AudioSystem::GetSingletonPtr()->play(PLAYING_BACKGROUND, 10, true);
	//���š���ս��ʼ����ʾ��;
	AudioSystem::GetSingletonPtr()->play(ALERT, 5, false);
}

void PlayingState::exit()
{
	m_pSceneMgr->destroyAllCameras();
	m_pRenderWnd->removeAllViewports();
	destroyScene();
	destroyUI();
}

void PlayingState::pause()
{

}

void PlayingState::resume()
{

}

void PlayingState::update(float timeSinceLaseFrame)
{
	//����tank�������淢��tank��Ϣ��;
	tank_m60->Update();
//	tank_t46->Update();


	//�����ӵ�������;
	BulletManager::getSingletonPtr()->Update();
	std::string collisionName = BulletManager::getSingletonPtr()->GetCollisionName();
	if (collisionName != "NULL")
	{
		int a = 0;
	}

	//���´���tankList;
	if (!m_TankList.empty())
	{
		map<std::string, BaseTank*>::iterator tankItr = m_TankList.begin();
		while( tankItr != m_TankList.end())
		{
			if (m_TankList.empty())
			{
				break;
			}

			if ( !tankItr->second->isLived())
			{
				//����tank;
				BaseTank *_tank = tankItr->second;
				m_TankList.erase(tankItr);
				delete _tank;
			}

			if (m_TankList.empty())
			{
				break;
			}

			++tankItr;
		}
	}


	//����tank��;
	if (MyGameCommand::GetSingletonPtr()->isServerOwner)
	{//����Ƿ����;
		MyServerNetworkSystem::GetSingletonPtr()->update(timeSinceLaseFrame);
	}

	//��������ϵͳ;
	MyClientNetworkSystem::GetSingletonPtr()->update(timeSinceLaseFrame);
}
 
void PlayingState::createScene()
{

	//��ͼ����;
	Ogre::DotSceneLoader loader;
	loader.parseDotScene("camp_map_3.scene", "General", m_pSceneMgr);

	//������պ�;
	//m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
	m_pSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

	std::string _tankName = MyGameCommand::GetSingletonPtr()->mSelfTankName;
	//����̹��;
	tank_m60 = new M60(_tankName);
	//tank_t46 = new T46();
}

void PlayingState::createCamera()
{
	m_pSceneMgr->destroyAllCameras();
	m_pRenderWnd->removeAllViewports();

	m_pCamera	= m_pSceneMgr->createCamera("PlayingCamera");
	//m_pCamera->setPosition(tank_m60->getPosition() + Ogre::Vector3(200, 200, 200));
	//m_pCamera->lookAt(tank_m60->getPosition());
	//m_pCamera->setFixedYawAxis(true);
	m_pCamera->setNearClipDistance(5);

	m_pViewport	= m_pRenderWnd->addViewport(m_pCamera);
	m_pCamera->setAspectRatio((float)m_pViewport->getActualWidth() / (float)m_pViewport->getActualHeight());
	m_pViewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	//�������һ��̹����;
	tank_m60->bindWithCamera(m_pCamera);
}

void PlayingState::createLight()
{
	//m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.1f, 1.0f, 1.0f));

	Ogre::Light	*_light	= m_pSceneMgr->createLight("PlayingLight");
	_light->setType(Ogre::Light::LT_DIRECTIONAL);
	/*_light->setPosition(0, 200, 0);*/
	_light->setDiffuseColour(1.0f, 1.0f, 1.0f);
	_light->setDirection(Ogre::Vector3(1, -1, 0));
}

void PlayingState::createUI()
{
	MyGUIManager::getSingletonPtr()->loadWindow("UI");
}

void PlayingState::createUIEvent()
{
	MyGUIManager::getSingletonPtr()->subscribeEvent("ok",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&PlayingState::onOK, this));

	MyGUIManager::getSingletonPtr()->subscribeEvent("cancel",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&PlayingState::onCancel, this));

	MyGUIManager::getSingletonPtr()->subscribeEvent("yes",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&PlayingState::onReplayYES, this));

	MyGUIManager::getSingletonPtr()->subscribeEvent("no",
		CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&PlayingState::onReplayNO, this));
}

void PlayingState::createNetWork()
{
	//�����ͷ���;
	MyClientNetworkSystem::GetSingletonPtr();

	//����Ƿ����,����;
	if (MyGameCommand::GetSingletonPtr()->isServerOwner)
	{
		MyServerNetworkSystem::GetSingletonPtr();
	}

	//���ӵ�������;(ip����Ҫ��ȡ)
	MyClientNetworkSystem::GetSingletonPtr()->ConnectToTheServer("10.253.115.21");
}

void PlayingState::destroyScene()
{
	GameApp::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");
	if (m_pSceneMgr)
		m_pRoot->destroySceneManager(m_pSceneMgr);
}

void PlayingState::destroyUI()
{
	
}

bool PlayingState::onOK(const CEGUI::EventArgs& evt)
{
	//StateManager::getSingletonPtr()->changeState(MainMenuState::getSingletonPtr());
	GameApp::getSingletonPtr()->shutdown();
	return true;
}

bool PlayingState::onCancel(const CEGUI::EventArgs& evt)
{
	m_isShowExit = false;
	MyGUIManager::getSingletonPtr()->getWindow("Exit")->setVisible(false);
	MyGUIManager::getSingletonPtr()->showGUICursor(false);
	return true;
}

bool PlayingState::onReplayYES(const CEGUI::EventArgs& evt)
{
	return true;
}

bool PlayingState::onReplayNO(const CEGUI::EventArgs& evt)
{
	return true;
}

void PlayingState::checkCollision()
{
	//�ӵ���tank֮�䣻

	//�ӵ������֮��;
}

bool PlayingState::keyPressed(const OIS::KeyEvent&evt)
{
	switch(evt.key)
	{
	case OIS::KC_ESCAPE:	//�˳���Ϸ;
		m_isShowExit = true;
		MyGUIManager::getSingletonPtr()->getWindow("Exit")->show();
		MyGUIManager::getSingletonPtr()->showGUICursor(true);

		//GameApp::getSingletonPtr()->shutdown();
		break;
	case OIS::KC_E:
		tank_m60->bindWithCamera(m_pCamera);
		break;
	case OIS::KC_R:
		tank_m60->unBindWithCamera(m_pCamera);
		break;
	case OIS::KC_B:
		m_isShowExit = true;
		MyGUIManager::getSingletonPtr()->getWindow("Exit")->show();
		MyGUIManager::getSingletonPtr()->showGUICursor(true);
		break;
	
	default:
		break;
	}

	//������Ӧtank��ʵ�ֶ�tank�Ŀ���;
	if (tank_m60)
	{
		return tank_m60->keyPressed(evt);
	}
	return true;
}

bool PlayingState::keyReleased(const OIS::KeyEvent&evt)
{
	if (tank_m60)
	{
		return tank_m60->keyReleased(evt);
	}
	return true;
}

bool PlayingState::mouseMoved(const OIS::MouseEvent&evt)
{
	if (m_isShowExit)
	{
		OIS::MouseState state = evt.state;
		MyGUIManager::getSingletonPtr()->injectMouseMove(state.X.rel, state.Y.rel);
	}
	else
	{
		Ogre::Real deltaYaw		= -0.0005 * evt.state.X.rel;
		Ogre::Real deltaPitch	= 0.0005 * evt.state.Y.rel;

		CommonNetWorkProtocal::MouseInfo _mouseInfo;

		std::string  TankName;
		TankName = tank_m60->getTankName();
		memset(&_mouseInfo,0,sizeof(_mouseInfo));
		memcpy_s(_mouseInfo.tankName,CommonNetWorkProtocal::MaxStrLen,TankName.c_str(),TankName.length());
		_mouseInfo.deltaYaw=deltaYaw;
		_mouseInfo.deltaPitch=deltaPitch;


		MyClientNetworkSystem::GetSingletonPtr()->SendPlayerControlSyncData(_mouseInfo);
		tank_m60->setFireDirection(deltaYaw, deltaPitch);
	}
	

	return true;
}

bool PlayingState::mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id)
{
	if (m_isShowExit)
	{
		MyGUIManager::getSingletonPtr()->injectMouseButtonDown(MyGUIManager::convertButton(id));
	}

	return true;
}

bool PlayingState::mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id)
{
	if (m_isShowExit)
	{
		MyGUIManager::getSingletonPtr()->injectMouseButtonUp(MyGUIManager::convertButton(id));
	}

	return true;
}

//tank�Ƿ����б���;
bool PlayingState::isTankInList(std::string &_tankName)
{
	map<std::string, BaseTank*>::iterator itr;
	itr = m_TankList.find(_tankName);
	if (itr != m_TankList.end())
	{
		//�ҵ�tank;
		return true;
	}

	return false;
}

BaseTank*	PlayingState::createTank(string name)
{
	BaseTank* tank;
	tank = new M60(name);
	return tank;
}

void PlayingState::DealTankSync(CommonNetWorkProtocal::TankInfo _tankInfo)
{
	CommonNetWorkProtocal::TankInfo tankInfo;
	tankInfo = _tankInfo;

	map<string, BaseTank*>::iterator tankItr;
	tankItr = m_TankList.find(tankInfo.tankName);

	if(tankItr == m_TankList.end() && tank_m60->getTankName() != tankInfo.tankName)
	{//����һ��tank;
		BaseTank* tank = createTank(tankInfo.tankName);
		tank->setPosition(Ogre::Vector3(tankInfo.syncdata.x_position, tankInfo.syncdata.y_position, tankInfo.syncdata.z_position));

		m_TankList.insert(make_pair(tankInfo.tankName, tank));
	}
	else
	{//���µ�ǰtank;
     //cout<<"";
		//ȡ��������Ϣ;
		if (!m_TankList.empty() && (tank_m60->getTankName() != tankInfo.tankName))
		{
			Ogre::Vector3 _tankPosition = Ogre::Vector3(tankInfo.syncdata.x_position, tankInfo.syncdata.y_position, tankInfo.syncdata.z_position);
			tankItr->second->setPosition(_tankPosition);
			if (tankInfo.syncdata.m_bIsTurnLeft)
			{
				tankItr->second->turnLeft();
			}

			if (tankInfo.syncdata.m_bIsTurnRight)
			{
					tankItr->second->turnRight();
			}

			/*if (tankInfo.syncdata.m_bIsFire)
			{
				tankItr->second->fire();
			}*/

			if (tankInfo.syncdata.x_position>-20)
			{
				int x=tankInfo.syncdata.x_position;
			}

			

		}

	}
}

void PlayingState::DealTankControlSync(CommonNetWorkProtocal::MouseInfo _mouseInfo){

	CommonNetWorkProtocal::MouseInfo mouseInfo;
	mouseInfo = _mouseInfo;

	map<string, BaseTank*>::iterator tankItr;

	tankItr = m_TankList.find(mouseInfo.tankName);

	if (tankItr!=m_TankList.end())
	{
		tankItr->second->setFireDirection(mouseInfo.deltaYaw,mouseInfo.deltaPitch);
	}
	
}


void PlayingState::DealTankFireSync(CommonNetWorkProtocal::FireInfo _fireInfo){
	CommonNetWorkProtocal::FireInfo fireInfo;
	fireInfo = _fireInfo;

	map<string, BaseTank*>::iterator tankItr;

	tankItr = m_TankList.find(fireInfo.tankName);

	if (tankItr!=m_TankList.end()) //�ҵ�;
	{
		tankItr->second->fire();
	}
}

void PlayingState::DealTankBulletCollisionSync(CommonNetWorkProtocal::BulletCollisionInfo _bulletCollisionInfo ){
	CommonNetWorkProtocal::BulletCollisionInfo bulletCollisionInfo;
	bulletCollisionInfo = _bulletCollisionInfo;

	map<string, BaseTank*>::iterator tankItr;

	tankItr = m_TankList.find(bulletCollisionInfo.tankName);

	if (tankItr!=m_TankList.end())//�ҵ���tank;
	{
		//��Ѫ
		tankItr->second->hurt();
	}
}