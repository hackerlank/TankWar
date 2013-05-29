/*
 * BulletManager.h
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include <list>
#include <Ogre.h>
#include "../Common/SingletonT.h"

class BaseBullet;
enum Bullet
{
	Vertical,
	Rocket,
};

class BulletManager : public SingletonT<BulletManager>
{
	SINGLETON_DEFINE(BulletManager)
	
public:
	BulletManager();
	~BulletManager();
	void CreateBullet(std::string owner, Bullet BulletType,Ogre::Vector3 direction,Ogre::Vector3 position,Ogre::Vector3 LastPositio);
	void Update();
	std::string GetCollisionName();
private:
	std::list<BaseBullet*> mBullets;
	
};