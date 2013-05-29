/*
 * BulletManager.h
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include <list>
#include <Ogre.h>
class BaseBullet;
enum Bullet
{
	Vertical,
	Rocket,
};
class BulletManager
{
	
public:
	BulletManager();
	~BulletManager();
	void CreateBullet(Bullet BulletName,Ogre::Vector3 direction,Ogre::Vector3 position,Ogre::Vector3 LastPositio);
	void Update();
	std::string GetCollisionName();
private:
	std::list<BaseBullet*> mBullets;
	
};