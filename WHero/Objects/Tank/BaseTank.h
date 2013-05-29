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
	
	//��ȡtank����;
	std::string     getTankName(){return  m_tankName;}
	//��ȡ̹�����λ��;
	Ogre::Vector3	getPosition(){ return m_pBodyNode->getPosition(); }
	//����tank��λ��;
	void		setPosition(Ogre::Vector3 _position)
	{
		 m_pBodyNode->setPosition(_position);
		 m_pUpperNode->setPosition(_position);
	 }
	//��ȡtank�ĳ���;
	Ogre::Vector3	getDirection(){ return Ogre::Vector3(Ogre::Math::Cos(m_bodyDirection), 0, Ogre::Math::Sin(m_bodyDirection)); } 


	//void		setDirection(Ogre::Vector3 _direction){ }
	Ogre::Vector3	getLookAtPosition(){ return m_pLookAt->getPosition() + m_pFireNode->getPosition() + m_pUpperNode->getPosition();}
	Ogre::Vector3	getFirePosition(){ return m_pFireNode->getPosition() + m_pUpperNode->getPosition(); }

	//����ǹͷ�ķ���;
	void	setFireDirection(Ogre::Real delteaYaw, Ogre::Real deltaPitch);
	//��ȡ��������;
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

	//---------------------------------------------����tank�Ĳ���-----------------------------------------
	//����ת;
	void	turnLeft(void);
	//����ת;
	void	turnRight(void);


	//��ǰ�н�;
	void	moveUp(void);
	//�����;
	void	moveBack(void);

	//���ݵ�ǰ���򣬵�ǰʹ�õ��ӵ�������;
	virtual void	fire(void);

	//---------------------------------------------------------------------------------------------------------

	//��һ�����������̹����;
	void	bindWithCamera(Ogre::Camera* _camera);
	//ȡ����̹���ϵ����;
	void	unBindWithCamera(Ogre::Camera* _camera);

	//��ײ��⣬�����������ײ���򷵻�true;
	bool	isCollision(const Ogre::Vector3& position, const Ogre::Vector3& direction, Ogre::Real RaySize);

	//------------------------------------------------�¼�����--------------------------------------------------

	virtual bool keyPressed(const OIS::KeyEvent&evt){ return true; }
	virtual bool keyReleased(const OIS::KeyEvent&evt){ return true; }
	virtual bool mouseMoved(const OIS::MouseEvent&evt){ return true; }
	virtual bool mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id){ return true; }
	virtual bool mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id){ return true; }

protected:
	Ogre::SceneManager		*m_pSceneMgr;

	Ogre::Entity			*m_pBodyEntity;		//̹�����ʵ��;
	Ogre::Entity			*m_pFireEntity;		//̹��ǹͷ��ʵ��;
	Ogre::SceneNode			*m_pBodyNode;		//̹����ڵ�;
	Ogre::SceneNode			*m_pUpperNode;		//̹�����沿�ֵĽڵ�;
	Ogre::SceneNode			*m_pFireNode;		//̹��ǹͷ�ڵ�;
	Ogre::SceneNode			*m_pLookAt;		    //�������ǰ�����Ǹ��ڵ㣬Ҳ���ӵ��ĳ�����;

	Ogre::Real				m_TurnIncrement;  //̹��ÿ֡��ת�ĽǶ�;
	Ogre::Real				m_Scale;		  //̹�˵�������;

	Ogre::Real				m_bodyDirection;  //̹���壨����ǹͷ���ķ���;
	Ogre::Real				m_fireDirection;  //ǹͷ����;
	Ogre::Real				m_bodyLength;	  //̹�˵ĳ���;
	Ogre::Real				m_bodyHeight;	  //̹����ĸ߶�;
	Ogre::Real				m_fireLength;	 //ǹͷ�ĳ��ȳߴ�;
	Ogre::Real				m_fireHeight;	  //ǹͷ�ĸ߶ȳߴ磻
	Ogre::Real				m_movingSpeed;    //̹�˵��ƶ��ٶ�;

	std::string             m_tankName;       //̹������;
	Ogre::Real				m_health;		  //̹�˵�Ѫ��������״̬;

	bool					m_bIsTurnLeft;	  //�Ƿ��������ת;
	bool					m_bIsTurnRight;	  //�Ƿ��������ת;
	bool					m_bIsMoveup;	  //�Ƿ����ǰ��;
	bool					m_bIsMoveBack;     //�Ƿ���Ժ���;

	Ogre::RaySceneQuery		*m_pRaySceneQuery;

	
};
#endif