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
	mSpeed=30;       //�ӵ����ٶ�;
	Timer = 0;	
	BulletNum=BulletNum+BulletNum;
	 m_bodyLength=1;	
	 m_pBodyEntity=GameApp::getSingletonPtr()->getGameSceneMgr()->createEntity("mm"+BulletNum,"bullet_2.mesh");
	 m_pBodyNode=GameApp::getSingletonPtr()->getGameSceneMgr()->getRootSceneNode()->createChildSceneNode("BulletNode"+BulletNum);
	 m_pBodyNode->attachObject(m_pBodyEntity);/*BulletNum++;*/
	 m_pBodyNode->setScale(1, 1, 1);

	 //����ϵͳ;
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
		//ײ�����������ߵ��ӵ�����һ���������δ��ײ������,���ӵ��Զ�����;
		if (IsCollision())
		{
			//ֻ���Ǵ��������Լ�����Щ�ӵ�;
			if ((getOwner() == MyGameCommand::GetSingletonPtr()->mSelfTankName/* + "BodyEntity"*/) /*&& (PlayingState::getSingletonPtr()->isTankInList(GetCollisionName()))*/)							////////////////////////////////////Ҫ��//////////////////////////
			{
				if (PlayingState::getSingletonPtr()->isTankInList(GetCollisionName()))
				{
					//�ϴ��з���Ѫ��������;///////////////////////////
					CommonNetWorkProtocal::BulletCollisionInfo _collisionInfo;
					std::string TankName = GetCollisionName();
					memset(&_collisionInfo, 0, sizeof(_collisionInfo));
					memcpy_s(_collisionInfo.tankName, CommonNetWorkProtocal::MaxStrLen, TankName.c_str(), TankName.length());

					MyClientNetworkSystem::GetSingletonPtr()->SendPlayerBulletCollisionSyncData(_collisionInfo);
				}
				
			}

			//�����ӵ�,����Ч��;
			//SetExistfalse();
		}
		//δײ�������������ǰ�������ӵ�����һ���������δ��ײ�����壬���Զ�����;
		else
		{
			mPosition += mSpeed*(mDirection/mDirection.normalise());
			m_pBodyNode->setPosition(mPosition);
			//ʵ������ʱ������Ч��;
		}
	}


}
void RocketBullet::Destroy()
{
	if ((IsExist)&&(!IsAppear))
	{
		//����ʱ����Ч��
		Timer++;
		if (Timer>20)
		{
			IsExist=false;
		}

			mSpeed=0;
	}

}
