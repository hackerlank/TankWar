#include "BaseTank.h"
#include "../Bullet/BulletManager.h"

BaseTank::BaseTank()
	:
	m_pBodyEntity(NULL),
	m_pFireEntity(NULL),
	m_pBodyNode(NULL),
	m_pUpperNode(NULL),
	m_pFireNode(NULL),
	m_pLookAt(NULL),
	m_bodyLength(0.0f),
	m_bodyHeight(0.0f),
	m_fireLength(0.0f),
	m_fireHeight(0.0f),
	m_TurnIncrement(Ogre::Math::PI/350),
	m_Scale(0.01),
	m_bodyDirection(Ogre::Math::PI/2),
	m_movingSpeed(0.0f),
	m_bIsTurnLeft(false),
	m_bIsTurnRight(false),
	m_bIsMoveup(false),
	m_bIsMoveBack(false)
{
	

}

BaseTank::~BaseTank()
{
	//m_pBodyNode->detachObject(m_pBodyEntity);
	//m_pFireNode->detachObject(m_pFireEntity);
	//GameApp::getSingletonPtr()->getGameSceneMgr()->destroyEntity(m_pBodyEntity);
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroyEntity(m_pFireEntity);
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroySceneNode(m_pBodyNode);
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroySceneNode(m_pFireNode);
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroySceneNode(m_pUpperNode);
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroySceneNode(m_pLookAt);
	GameApp::getSingletonPtr()->getGameSceneMgr()->destroyQuery(m_pRaySceneQuery);
}

void BaseTank::turnLeft()
{
	m_bodyDirection -= m_TurnIncrement;
	m_pBodyNode->yaw(Ogre::Radian(m_TurnIncrement));
}

void BaseTank::turnRight()
{
	m_bodyDirection += m_TurnIncrement;
	m_pBodyNode->yaw(Ogre::Radian(-m_TurnIncrement));
}

//转动枪头;
void BaseTank::setFireDirection(Ogre::Real delteaYaw, Ogre::Real deltaPitch)
{
	m_pUpperNode->yaw(Ogre::Radian(delteaYaw), Ogre::Node::TS_WORLD);
	m_pUpperNode->pitch(Ogre::Radian(deltaPitch), Ogre::Node::TS_LOCAL);
}

void BaseTank::moveUp()
{
	m_pBodyNode->translate(getDirection() * m_movingSpeed);
	m_pUpperNode->translate(getDirection() * m_movingSpeed);
}

void BaseTank::moveBack()
{
	m_pBodyNode->translate(-1 * getDirection() * m_movingSpeed);
	m_pUpperNode->translate(-1 * getDirection() * m_movingSpeed);
}

//根据初始位置和方向发射子弹;
void BaseTank::fire()
{
	//Ogre::Vector3 position = getPosition() + getDirection().normalise()*(m_bodyLength);
	Ogre::Vector3 position = m_pLookAt->_getDerivedPosition()/*m_pLookAt->getPosition() + m_pFireNode->getPosition() + m_pUpperNode->getPosition()*/;

	BulletManager::getSingletonPtr()->CreateBullet(getTankName(), Rocket, getShootingDirection(), position, Ogre::Vector3(0,0,0));
}

//绑定摄像机到tank上;
void BaseTank::bindWithCamera(Ogre::Camera* _camera)
{
	//按照坦克设置摄像机的位置和朝向;
	Ogre::Vector3	_tankFirePos = m_pUpperNode->getPosition();
	_camera->setPosition(/*_tankFirePos + */
		/*m_pFireNode->_getDerivedPosition() + */Ogre::Vector3::UNIT_Y*m_fireHeight*4 + Ogre::Vector3(0, 0, -m_fireLength*(1.5)));  //0,20,0

// 	_camera->setPosition(/*_tankFirePos + */Ogre::Vector3(0,
// 		50/*m_pFireNode->_getDerivedPosition() + m_l*/, -20));

	_camera->lookAt(this->getDirection()*70);
	//_camera->lookAt(m_pLookAt->_getDerivedPosition());

	//实现绑定;
	this->m_pUpperNode->attachObject(_camera);
}

void BaseTank::unBindWithCamera(Ogre::Camera* _camera)
{
	this->m_pUpperNode->detachObject(_camera);

	//重新设置相机的位置;
	_camera->setPosition(Ogre::Vector3(100, 400, 100));
	_camera->lookAt(Ogre::Vector3(0, 0, 0));
}


bool BaseTank::isCollision(const Ogre::Vector3& position, const Ogre::Vector3& direction, Ogre::Real RaySize)
{
	//根据初始位置和方向创建一条射线;
	Ogre::Ray ray(position, direction);
	m_pRaySceneQuery->setRay(ray);
	//获取射线查询结果;
	Ogre::RaySceneQueryResult	&result = m_pRaySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator ite;
	//遍历查询结果，对每个结果做相应的操作;
	for( ite = result.begin(); ite!=result.end(); ite++)
	{
		//如果在指定距离的射线范围内查找到实体，则返回true;
		Ogre::String p=m_pBodyEntity->getName();
		if (ite->movable->getName().compare(m_pBodyEntity->getName()) != 0
			&& ite->distance < RaySize)
		{
			if (ite->movable->getName() != "PlayingCamera")
			{
					return true;
			}
		}
	}
	return false;
}