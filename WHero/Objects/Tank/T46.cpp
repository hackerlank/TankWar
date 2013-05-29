#include "T46.h"


T46::T46(void)
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getGameSceneMgr();

	//坦克体;
	m_pBodyEntity = m_pSceneMgr->createEntity("t46_Entity", "ogrehead.mesh");
	m_pBodyNode	= m_pSceneMgr->getRootSceneNode()->createChildSceneNode("t46_BodyNode");
	//m_pBodyNode->setScale(0.5, 0.5, 0.5);
	m_pBodyNode->setPosition(Ogre::Vector3(0, 100, 50));
	m_pBodyNode->attachObject(m_pBodyEntity);
	m_pBodyNode->showBoundingBox(true);

	//创建一个射线查询;
	m_pRaySceneQuery = m_pSceneMgr->createRayQuery(Ogre::Ray());

	//获取实体的尺寸;
	Ogre::AxisAlignedBox box = m_pBodyEntity->getBoundingBox();
	m_bodyHeight = box.getSize().x;

	int a = 0;
}

T46::~T46(void)
{
}

void T46::Update()
{
	//保证实体在一个地形上面行走;
	if (!isCollision(m_pBodyNode->getPosition(), Ogre::Vector3(0, -1, 0), m_bodyHeight))
	{
		m_pBodyNode->translate(Ogre::Vector3(0, -0.5, 0));
	}
}
