#include "BaseTank.h"

BaseTank::BaseTank()
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getGameSceneMgr();

	//Ì¹¿ËÌå;
	m_pBodyEntity = m_pSceneMgr->createEntity("tankBodyEntity", "ogrehead.mesh");
	m_pBodyNode	= m_pSceneMgr->getRootSceneNode()->createChildSceneNode("tankBodyNode");
	m_pBodyNode->attachObject(m_pBodyEntity);
}

BaseTank::~BaseTank()
{

}