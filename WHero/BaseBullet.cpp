/* 
* BaseBullet.cpp
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include "BaseBullet.h"

#include "GameApp.h"
BaseBullet::BaseBullet()															
{
	//m_pBodyEntity=GameApp::getSingletonPtr()->getGameSceneMgr()->createEntity("mm"+BulletNum,"ogrehead.mesh");
	//m_pBodyNode=GameApp::getSingletonPtr()->getGameSceneMgr()->getRootSceneNode()->createChildSceneNode("BulletNode"+BulletNum);
	//m_pBodyNode->attachObject(m_pBodyEntity);/*BulletNum++;*/


	//BulletNum++;

	IsExist=true;
	IsAppear=true;
	m_pCollisionName="NULL";

	m_pRaySceneQuery = GameApp::getSingletonPtr()->getGameSceneMgr()->createRayQuery(Ogre::Ray());
	
}
BaseBullet::~BaseBullet()
{
	delete m_pBodyEntity;
	delete m_pBodyNode;
}
void BaseBullet::SetDirection(Ogre::Vector3 vec)
{
	mDirection=vec;
}
void BaseBullet::SetOriginalPosition(Ogre::Vector3 vec)
{
	mPosition=vec;
}
bool BaseBullet::Existene(void)
{
	return IsExist;
}
bool BaseBullet::Appear(void)
{
	return IsAppear;
}
void BaseBullet::SetDistance(float Dis)
{

}
void BaseBullet::SetExistfalse(void)
{
	IsExist=false;
}
bool BaseBullet::IsCollision(void)
{
	Ogre::Vector3 m=Ogre::Vector3(20,20,20);
	Ogre::Vector3 n=Ogre::Vector3(20,0,20);
	Ogre::Ray ray(mPosition+m, Ogre::Vector3(0, -1, 0));
	m_pRaySceneQuery->setRay(ray);
	Ogre::RaySceneQueryResult	&result = m_pRaySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator ite;
	for( ite = result.begin(); ite!=result.end(); ite++)
	{
		int m=ite->movable->getName().compare(m_pBodyEntity->getName());
		int n=ite->distance;
		Ogre::String p=m_pBodyEntity->getName();
		if (ite->movable->getName().compare(m_pBodyEntity->getName()) != 0
			&& ite->distance < m_bodyLength/2)
		{
			/*IsAppear=false;*/
			m_pCollisionName=ite->movable->getName();
			return true;
		}
	}
	return false;
}
std::string BaseBullet ::GetCollisionName()
{
	if(m_pCollisionName.empty())
		return "NULL";
	else
		return m_pCollisionName;
}
