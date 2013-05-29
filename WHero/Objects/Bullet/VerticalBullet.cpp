/*
 * VerticalBullet.cpp
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include "VerticalBullet.h"
#include "../GameApp.h"
VerticalBullet::VerticalBullet()
{
	mSpeed=20;
	IsExist=true;
	IsAppear=true;
	Timer=0;
	mDistance=100;


	m_pBodyEntity=GameApp::getSingletonPtr()->getGameSceneMgr()->createEntity("mm"+BulletNum,"ogrehead.mesh");
	m_pBodyNode=GameApp::getSingletonPtr()->getGameSceneMgr()->getRootSceneNode()->createChildSceneNode("BulletNode"+BulletNum);
	m_pBodyNode->attachObject(m_pBodyEntity);/*BulletNum++;*/

}
VerticalBullet::~VerticalBullet()
{

}
void VerticalBullet::Update()
{
	if ((IsExist)&&(IsAppear))
	{
		//运动时粒子效果

		m_pBodyNode->setPosition(mPosition);
	}
}
void VerticalBullet::Destroy()
{
	IsAppear=false;
	if ((IsExist)&&(IsAppear))
	{
		//销毁时粒子效果
		Timer++;
		if (Timer>80)
		{
			IsAppear=false;
		}
	}
	mSpeed=0;
}
void VerticalBullet::SetDistance(float Dis)
{
	mDistance=Dis;
}


