/*
 * RocketBullet.h 
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include "RocketBullet.h"
#include "../GameApp.h"
RocketBullet::RocketBullet()

{
	mSpeed=0.1;
	BulletNum=BulletNum+BulletNum;
	 m_bodyLength=10;	
	 m_pBodyEntity=GameApp::getSingletonPtr()->getGameSceneMgr()->createEntity("mm"+BulletNum,"ogrehead.mesh");
	 m_pBodyNode=GameApp::getSingletonPtr()->getGameSceneMgr()->getRootSceneNode()->createChildSceneNode("BulletNode"+BulletNum);
	 m_pBodyNode->attachObject(m_pBodyEntity);/*BulletNum++;*/


	 

}
RocketBullet::~RocketBullet()
{

}
void RocketBullet::Update()
{
	
	if((IsAppear)&&(IsExist)/*&&(!IsCollision())*/)
	{
		mPosition+=mSpeed*mDirection;
		m_pBodyNode->setPosition(mPosition);
		//实现运行时的粒子效果
	}


}
void RocketBullet::Destroy()
{
	if ((IsExist)&&(!IsAppear))
	{
		//销毁时粒子效果
		Timer++;
		if (Timer>80)
		{
			IsExist=false;
		}

			mSpeed=0;
	}

}
