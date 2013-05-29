/*
 * BaseBullet.h
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#ifndef BASEBULLET_H_
#define BASEBULLET_H_
#include "Ogre.h"
#include <string>
static std::string BulletNum="m";
class BaseBullet
{
public:
	BaseBullet();
	virtual~BaseBullet();
	virtual void SetOriginalPosition(Ogre::Vector3 vec);
	virtual void SetDirection(Ogre::Vector3 vec);

	virtual void Update()=0;                   //�ӵ��ƶ�ʱ�ĸ���Ч��
	virtual void Destroy()=0;					//�ӵ�����ʱ�ĸ���Ч��

	virtual bool Existene(void);
	virtual bool Appear(void);
	virtual bool IsCollision(void);
	virtual void SetDistance(float Dis);             //���ù�������ĳ���
	virtual void SetExistfalse(void);						//�����ӵ�
	/*virtual void GetCollisionName(void);*/           //���ӵ���ײ�󣬻�ȡ����ʵ�������
	virtual std::string GetCollisionName(void);
	
protected:
	
	
	bool IsExist;								//�ӵ��Ƿ�ݻ�
	bool IsAppear;								//�ӵ��Ƿ���ʾ
	float	Timer;								//�ӵ����ٺ�Ч���ӳ�ʱ��
	float mDistance;                            //�ӵ�Ҫ�򵽵ľ���

	float					m_bodyLength; 		//�ӵ��ĳ���

	Ogre::Vector3			mSpeed;						//�ӵ����ƶ��ٶ�
	Ogre::Vector3			mPosition;                   //�ӵ���ʼλ��
	Ogre::Vector3			mDirection;					//�ӵ���ʼ����
	Ogre::Entity*			m_pBodyEntity;
	Ogre::SceneNode*		m_pBodyNode;
	Ogre::RaySceneQuery*	m_pRaySceneQuery;    //���߼��
	std::string				m_pCollisionName;    //�ӵ���ײ�󣬻�ȡ���ӵ�������ײʵ�������

};

#endif