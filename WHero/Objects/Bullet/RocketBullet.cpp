/*
 * RocketBullet.h 
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include "RocketBullet.h"
#include "../GameApp.h"
#include "../State/PlayingState.h"
#include "../NetWork/MyGameCommand.h"
#include "../NetWork/CommonNetWorkProtocal.h"
#include "../NetWork/MyClientNetworkSystem.h"

RocketBullet::RocketBullet()
{
	mSpeed=30;       //子弹的速度;
	Timer = 0;	
	BulletNum=BulletNum+BulletNum;
	 m_bodyLength=1;	
	 m_pBodyEntity=GameApp::getSingletonPtr()->getGameSceneMgr()->createEntity("mm"+BulletNum,"bullet_2.mesh");
	 m_pBodyNode=GameApp::getSingletonPtr()->getGameSceneMgr()->getRootSceneNode()->createChildSceneNode("BulletNode"+BulletNum);
	 m_pBodyNode->attachObject(m_pBodyEntity);/*BulletNum++;*/
	 m_pBodyNode->setScale(1, 1, 1);

	 //粒子系统;
	 Ogre::ParticleSystem*	 mm_pPartclesAppear=GameApp::getSingletonPtr()->getGameSceneMgr()->createParticleSystem(BulletNum,"Examples/Smoke");
	 Ogre::SceneNode *mm_pPartcleAppearNode=m_pBodyNode->createChildSceneNode();
	 mm_pPartcleAppearNode->attachObject(mm_pPartclesAppear);

}

RocketBullet::~RocketBullet()
{

}
void RocketBullet::Update()
{
	
	if((IsAppear)&&(IsExist)/*&&(!IsCollision())*/)
	{
		//撞倒东西，或者当子弹到达一定距离后任未碰撞到物体,则子弹自动销毁;
		if (IsCollision())
		{
			//只考虑从属者是自己的那些子弹;
			if ((getOwner() == MyGameCommand::GetSingletonPtr()->mSelfTankName/* + "BodyEntity"*/) /*&& (PlayingState::getSingletonPtr()->isTankInList(GetCollisionName()))*/)							////////////////////////////////////要改//////////////////////////
			{
				if (PlayingState::getSingletonPtr()->isTankInList(GetCollisionName()))
				{
					//上传敌方掉血申请数据;///////////////////////////
					CommonNetWorkProtocal::BulletCollisionInfo _collisionInfo;
					std::string TankName = GetCollisionName();
					memset(&_collisionInfo, 0, sizeof(_collisionInfo));
					memcpy_s(_collisionInfo.tankName, CommonNetWorkProtocal::MaxStrLen, TankName.c_str(), TankName.length());

					MyClientNetworkSystem::GetSingletonPtr()->SendPlayerBulletCollisionSyncData(_collisionInfo);
				}
				
			}

			//销毁子弹,粒子效果;
			//SetExistfalse();
		}
		//未撞倒东西，则继续前进，当子弹到达一定距离后任未碰撞到物体，则自动销毁;
		else
		{
			mPosition += mSpeed*(mDirection/mDirection.normalise());
			m_pBodyNode->setPosition(mPosition);
			//实现运行时的粒子效果;
		}
	}


}
void RocketBullet::Destroy()
{
	if ((IsExist)&&(!IsAppear))
	{
		//销毁时粒子效果
		Timer++;
		if (Timer>20)
		{
			IsExist=false;
		}

			mSpeed=0;
	}

}
