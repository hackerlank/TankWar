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

	virtual void Update()=0;                   //子弹移动时的更新效果
	virtual void Destroy()=0;					//子弹销毁时的更新效果

	virtual bool Existene(void);
	virtual bool Appear(void);
	virtual bool IsCollision(void);
	virtual void SetDistance(float Dis);             //设置攻击距离的长短
	virtual void SetExistfalse(void);						//销毁子弹
	/*virtual void GetCollisionName(void);*/           //当子弹碰撞后，获取被碰实体的名字
	virtual std::string GetCollisionName(void);
	
protected:
	
	
	bool IsExist;								//子弹是否摧毁
	bool IsAppear;								//子弹是否显示
	float	Timer;								//子弹销毁后效果延迟时间
	float mDistance;                            //子弹要打到的距离

	float					m_bodyLength; 		//子弹的长度

	Ogre::Vector3			mSpeed;						//子弹的移动速度
	Ogre::Vector3			mPosition;                   //子弹初始位置
	Ogre::Vector3			mDirection;					//子弹初始方向
	Ogre::Entity*			m_pBodyEntity;
	Ogre::SceneNode*		m_pBodyNode;
	Ogre::RaySceneQuery*	m_pRaySceneQuery;    //射线检测
	std::string				m_pCollisionName;    //子弹碰撞后，获取与子弹发生碰撞实体的名字

};

#endif