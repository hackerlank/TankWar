/*
 * BaseTank.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#ifndef BASETANK_H_
#define BASETANK_H_

#include <Ogre.h>
#include "../BaseObject.h"
#include "../GameApp.h"

class BaseTank : public BaseObject, public OIS::MouseListener, public OIS::KeyListener
{
public:
	BaseTank();
	virtual ~BaseTank();

	virtual void Update(){}
	
	//获取tank名字;
	std::string     getTankName(){return  m_tankName;}
	//获取坦克体的位置;
	Ogre::Vector3	getPosition(){ return m_pBodyNode->getPosition(); }
	//设置tank的位置;
	void		setPosition(Ogre::Vector3 _position)
	{
		 m_pBodyNode->setPosition(_position);
		 m_pUpperNode->setPosition(_position);
	 }
	//获取tank的朝向;
	Ogre::Vector3	getDirection(){ return Ogre::Vector3(Ogre::Math::Cos(m_bodyDirection), 0, Ogre::Math::Sin(m_bodyDirection)); } 


	//void		setDirection(Ogre::Vector3 _direction){ }
	Ogre::Vector3	getLookAtPosition(){ return m_pLookAt->getPosition() + m_pFireNode->getPosition() + m_pUpperNode->getPosition();}
	Ogre::Vector3	getFirePosition(){ return m_pFireNode->getPosition() + m_pUpperNode->getPosition(); }

	//设置枪头的方向;
	void	setFireDirection(Ogre::Real delteaYaw, Ogre::Real deltaPitch);
	//获取攻击方向;
	Ogre::Vector3	getShootingDirection()
	{ 
		//return getLookAtPosition() - getFirePosition();
		return m_pLookAt->_getDerivedPosition() - m_pFireNode->_getDerivedPosition();
		int a;
	}

	//--------------------------------------------------------------------------------------------------
	
	void		setHealth(Ogre::Real _health){ m_health = _health; }
	Ogre::Real	getHealth(){ return m_health; }
	//void		hurt(){ m_health -= 20; }   //////////////////20
    void		hurt(){ setHealth(getHealth() -20);}
	bool		isLived()
	{ 
		if (m_health >= 0)
		{
			return true;
		}
		return false;
	}

	//---------------------------------------------控制tank的操作-----------------------------------------
	//向左转;
	void	turnLeft(void);
	//向右转;
	void	turnRight(void);


	//向前行进;
	void	moveUp(void);
	//向后退;
	void	moveBack(void);

	//根据当前朝向，当前使用的子弹，攻击;
	virtual void	fire(void);

	//---------------------------------------------------------------------------------------------------------

	//绑定一个摄像机到该坦克上;
	void	bindWithCamera(Ogre::Camera* _camera);
	//取消绑定坦克上的相机;
	void	unBindWithCamera(Ogre::Camera* _camera);

	//碰撞检测，如果与物体相撞，则返回true;
	bool	isCollision(const Ogre::Vector3& position, const Ogre::Vector3& direction, Ogre::Real RaySize);

	//------------------------------------------------事件监听--------------------------------------------------

	virtual bool keyPressed(const OIS::KeyEvent&evt){ return true; }
	virtual bool keyReleased(const OIS::KeyEvent&evt){ return true; }
	virtual bool mouseMoved(const OIS::MouseEvent&evt){ return true; }
	virtual bool mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id){ return true; }
	virtual bool mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id){ return true; }

protected:
	Ogre::SceneManager		*m_pSceneMgr;

	Ogre::Entity			*m_pBodyEntity;		//坦克体的实体;
	Ogre::Entity			*m_pFireEntity;		//坦克枪头的实体;
	Ogre::SceneNode			*m_pBodyNode;		//坦克体节点;
	Ogre::SceneNode			*m_pUpperNode;		//坦克上面部分的节点;
	Ogre::SceneNode			*m_pFireNode;		//坦克枪头节点;
	Ogre::SceneNode			*m_pLookAt;		    //摄像机向前看的那个节点，也是子弹的出发点;

	Ogre::Real				m_TurnIncrement;  //坦克每帧旋转的角度;
	Ogre::Real				m_Scale;		  //坦克的缩放量;

	Ogre::Real				m_bodyDirection;  //坦克体（不是枪头）的方向;
	Ogre::Real				m_fireDirection;  //枪头方向;
	Ogre::Real				m_bodyLength;	  //坦克的长度;
	Ogre::Real				m_bodyHeight;	  //坦克体的高度;
	Ogre::Real				m_fireLength;	 //枪头的长度尺寸;
	Ogre::Real				m_fireHeight;	  //枪头的高度尺寸；
	Ogre::Real				m_movingSpeed;    //坦克的移动速度;

	std::string             m_tankName;       //坦克名字;
	Ogre::Real				m_health;		  //坦克的血量，健康状态;

	bool					m_bIsTurnLeft;	  //是否可以向左转;
	bool					m_bIsTurnRight;	  //是否可以向右转;
	bool					m_bIsMoveup;	  //是否可以前进;
	bool					m_bIsMoveBack;     //是否可以后退;

	Ogre::RaySceneQuery		*m_pRaySceneQuery;

	
};
#endif