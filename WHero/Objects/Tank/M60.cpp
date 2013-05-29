#include "M60.h"
#include "../NetWork/CommonNetWorkProtocal.h"
#include "../NetWork/MyGameCommand.h"
#include "../NetWork/MyClientNetworkSystem.h"
#include "../Audio/AudioSystem.h"

M60::M60(const std::string& name)
{
	m_tankName = name;
	m_health = 100;

	//MyGameCommand::GetSingleton().mSelfTankName = name;

	m_pSceneMgr = GameApp::getSingletonPtr()->getGameSceneMgr();

	//坦克体;(name + "bodyEntity")
	m_pBodyEntity = m_pSceneMgr->createEntity(name+"BodyEntity", "Part_2.mesh");
	m_pBodyNode	= m_pSceneMgr->getRootSceneNode()->createChildSceneNode(name+"BodyNode");
	m_pBodyNode->setScale(m_Scale, m_Scale, m_Scale);
	m_pBodyNode->attachObject(m_pBodyEntity);
	m_pBodyNode->setPosition(Ogre::Vector3(-50, 100, 300));
	//m_pBodyNode->showBoundingBox(true);
	//获取坦克体的尺寸;
	Ogre::AxisAlignedBox box = m_pBodyEntity->getBoundingBox();
	m_bodyLength = box.getSize().z*m_Scale;
	m_bodyHeight = box.getSize().y*m_Scale;

	//代表坦克上面部分的节点;(name + "fireEntity")
	m_pUpperNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(name+"UpperNode");
	m_pUpperNode->setPosition(m_pBodyNode->_getDerivedPosition() + Ogre::Vector3::UNIT_Y*m_bodyHeight/4);  //getPosition();
	m_pUpperNode->setFixedYawAxis(true);

	//枪头实体;
	m_pFireEntity = m_pSceneMgr->createEntity(name+"fireEntity", "Part_1.mesh");
	//枪头节点;(name + "fireEntity")
	m_pFireNode = m_pUpperNode->createChildSceneNode(name+"FireNode");
	m_pFireNode->attachObject(m_pFireEntity);
	m_pFireNode->setPosition(0, 0, 0);
	m_pFireNode->setScale(m_Scale, m_Scale, m_Scale);
	//获取枪头的尺寸信息;
	box = m_pFireEntity->getBoundingBox();
	m_fireLength = box.getSize().z *m_Scale;
	m_fireHeight = box.getSize().y *m_Scale;

	m_pLookAt = /*m_pFireNode*/m_pFireNode->createChildSceneNode(Ogre::Vector3(0, 0, m_fireLength*2/*m_bodyLength*//**m_Scale*//*/2*/));  //m_fireLength；
	//设置枪头的初始位置，实现初步与坦克体的绑定;(pos + fireEnt.size)
	//m_pFireNode->setPosition(m_pBodyNode->getPosition() + Ogre::Vector3(0, 30, 0));


	//创建一个射线查询;
	m_pRaySceneQuery = m_pSceneMgr->createRayQuery(Ogre::Ray());

	//坦克的各种参数设定;
	m_movingSpeed = 1.5f;
}

M60::~M60(void)
{
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroyEntity(m_pBodyEntity);
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroySceneNode(m_pBodyNode);
}

void M60::Update()
{
	//首先保证实体在一个地形上面;
	if (!isCollision(m_pBodyNode->getPosition(), Ogre::Vector3(0, -1, 0), m_bodyHeight/(1/**m_Scale*/)))
	{
		m_pBodyNode->translate(Ogre::Vector3(0, -m_movingSpeed, 0));
		m_pUpperNode->translate(Ogre::Vector3(0, -m_movingSpeed, 0));
	}

	//实体向左转;
	if (m_bIsTurnLeft)
	{
		turnLeft();
	}
	//实体向右转;
	if (m_bIsTurnRight)
	{
		turnRight();
	}
	//实体前进;
	if (m_bIsMoveup && !isCollision(m_pBodyNode->getPosition(), getDirection(), m_bodyLength/2))
	{
			moveUp();
	}
	//实体后退;
	if (m_bIsMoveBack && !isCollision(m_pBodyNode->getPosition(), -1*getDirection(), m_bodyLength/2))
	{
		moveBack();
	}

	//-----------------------------------------------------------
	//坦克信息打包;
	CommonNetWorkProtocal::TankInfo _tankInfo;

		std::string  TankName;
		TankName = m_tankName;
     memset(&_tankInfo,0,sizeof(_tankInfo));
     memcpy_s(_tankInfo.tankName,CommonNetWorkProtocal::MaxStrLen,TankName.c_str(),TankName.length());
	_tankInfo.syncdata.x_position = getPosition().x;
	_tankInfo.syncdata.y_position = getPosition().y;
	_tankInfo.syncdata.z_position = getPosition().z;

	_tankInfo.syncdata.m_bIsTurnLeft=this->m_bIsTurnLeft;
	_tankInfo.syncdata.m_bIsTurnRight=this->m_bIsTurnRight;

	//传输坦克信息包;
	MyClientNetworkSystem::GetSingletonPtr()->SendPlayerStateSyncData(_tankInfo);

}

bool M60::keyPressed(const OIS::KeyEvent&evt)
{
	switch(evt.key)
	{
	case OIS::KC_W:
		m_bIsMoveup = true;
		break;
	case  OIS::KC_S:
		m_bIsMoveBack = true;
		break;
	case OIS::KC_A:
		m_bIsTurnLeft = true;
		break;
	case OIS::KC_D:
		m_bIsTurnRight = true;
		break;
	case OIS::KC_SPACE:
		{
			//播放开苞声音;
			AudioSystem::GetSingletonPtr()->play(FIRE, 10, false);

			//打包开火信息
			CommonNetWorkProtocal::FireInfo _fireInfo;
			std::string  TankName;
			TankName = this->m_tankName;
			memset(&_fireInfo,0,sizeof(_fireInfo));
			memcpy_s(_fireInfo.tankName,CommonNetWorkProtocal::MaxStrLen,TankName.c_str(),TankName.length());

			MyClientNetworkSystem::GetSingletonPtr()->SendPlayerFireSyncData(_fireInfo);
		fire();}
		break;
	default:
		break;
	}
	return true;
}

bool M60::keyReleased(const OIS::KeyEvent&evt)
{
	if ((evt.key == OIS::KC_W) && (m_bIsMoveup == true)) 
	{
		m_bIsMoveup = false;
	}
	else if((evt.key == OIS::KC_S) && (m_bIsMoveBack == true))
	{
		m_bIsMoveBack = false;
	}
	else if((evt.key == OIS::KC_A) && (m_bIsTurnLeft == true))
	{
		m_bIsTurnLeft = false;
	}
	else if(evt.key == OIS::KC_D && (m_bIsTurnRight == true))
	{
		m_bIsTurnRight = false;
	}

	return true;
}

bool M60::mouseMoved(const OIS::MouseEvent&evt)
{
	return true;
}

bool M60::mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id)
{
	if (id == OIS::MB_Left)
	{
		fire();
	}
	return true;
}

bool M60::mouseReleased(const OIS::MouseEvent&fevt, OIS::MouseButtonID id)
{
	return true;
}