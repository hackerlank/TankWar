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
void BulletManager::CreateBullet(Bullet BulletName,Ogre::Vector3 direction,Ogre::Vector3 position,Ogre::Vector3 LastPosition)
{
	switch (BulletName)
	{
	case Rocket:
		{
			BaseBullet *newRoctetBullet=new RocketBullet();
			newRoctetBullet->SetDirection(direction);
			newRoctetBullet->SetOriginalPosition(position);
			mBullets.push_back(newRoctetBullet);
		}
		break;
	case Vertical:
		{
			BaseBullet *newVerticalBullet=new VerticalBullet();
			newVerticalBullet->SetDirection(direction);
			newVerticalBullet->SetOriginalPosition(position);
			/*newVerticalBullet->SetDistance();*/                      //后期修改，根据编变化
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
		for (;itr!=mBullets.end();itr++)
		{
			
			if ((*itr)->Existene())
			{
				(*itr)->Update();
				(*itr)->Destroy();
				
			} 
			else
			{
				BaseBullet *Bullet=*itr;
				mBullets.erase(itr);                               //****这里可能有问题****//
				delete Bullet;

			}

		}
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