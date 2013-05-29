/*
 * BulletManager.cpp
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include "BulletManager.h"
#include "RocketBullet.h"
#include "VerticalBullet.h"
#include "BaseBullet.h"

BulletManager::BulletManager()
{
	/*mBullets=NULL;*/
}
BulletManager::~BulletManager()
{

}

void BulletManager::CreateBullet(std::string tankName, Bullet BulletType,Ogre::Vector3 direction,Ogre::Vector3 position,Ogre::Vector3 LastPosition)
{
	switch (BulletType)
	{
	case Rocket:
		{
			BaseBullet *newRoctetBullet=new RocketBullet();
			newRoctetBullet->SetDirection(direction);
			newRoctetBullet->SetOriginalPosition(position);
			//���ô�����;
			newRoctetBullet->setOwner(tankName);
			mBullets.push_back(newRoctetBullet);
		}
		break;
	case Vertical:
		{
			BaseBullet *newVerticalBullet=new VerticalBullet();
			newVerticalBullet->SetDirection(direction);
			newVerticalBullet->SetOriginalPosition(position);
			/*newVerticalBullet->SetDistance();*/                      //�����޸ģ����ݱ�仯
			//���ô�����;
			newVerticalBullet->setOwner(tankName);
			mBullets.push_back(newVerticalBullet);
		
		}
		break;	
	}
}

void BulletManager::Update()
{
	if (!mBullets.empty())
	{
		std::list<BaseBullet*>::iterator itr=mBullets.begin();

		while(itr != mBullets.end())
		{
			if (mBullets.empty())  //
				break;
			if ((*itr)->Existene())
			{
				(*itr)->Update();
				(*itr)->Destroy();
			}
			else
			{
  				BaseBullet *bullet = *itr;
				delete  bullet;
				mBullets.erase(itr);
				itr = mBullets.begin();
			}

			if (mBullets.empty())
				break;
			++itr;
		}

// 		for (;itr!=mBullets.end();itr++)
// 		{
// 			
// 			if ((*itr)->Existene())  //�ӵ�����;
// 			{
// 				(*itr)->Update();
// 				(*itr)->Destroy();
// 				
// 			} 
// 			else	
// 			{
// 				BaseBullet *Bullet=*itr;
// 				itr = mBullets.erase(itr);                               //****�������������****//
// 				//delete Bullet;
// 
// 			}
// 
// 		}
	}

}

std::string BulletManager::GetCollisionName()
{

	if (!mBullets.empty())
	{
		std::list<BaseBullet*>::iterator itr=mBullets.begin();
		for (;itr!=mBullets.end();itr++)
		{
			return (*itr)->GetCollisionName();
		}
	}
	else
		return "NULL";
}