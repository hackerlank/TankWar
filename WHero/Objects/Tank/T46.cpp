#include "T46.h"


T46::T46(void)
{
	m_pSceneMgr = GameApp::getSingletonPtr()->getGameSceneMgr();

	//̹����;
	m_pBodyEntity = m_pSceneMgr->createEntity("t46_Entity", "ogrehead.mesh");
	m_pBodyNode	= m_pSceneMgr->getRootSceneNode()->createChildSceneNode("t46_BodyNode");
	//m_pBodyNode->setScale(0.5, 0.5, 0.5);
	m_pBodyNode->setPosition(Ogre::Vector3(0, 100, 50));
	m_pBodyNode->attachObject(m_pBodyEntity);
	m_pBodyNode->showBoundingBox(true);

	//����һ�����߲�ѯ;
	m_pRaySceneQuery = m_pSceneMgr->createRayQuery(Ogre::Ray());

	//��ȡʵ��ĳߴ�;
	Ogre::AxisAlignedBox box = m_pBodyEntity->getBoundingBox();
	m_bodyHeight = box.getSize().x;

	int a = 0;
}

T46::~T46(void)
{
}

void T46::Update()
{
	//��֤ʵ����һ��������������;
	if (!isCollision(m_pBodyNode->getPosition(), Ogre::Vector3(0, -1, 0), m_bodyHeight))
	{
		m_pBodyNode->translate(Ogre::Vector3(0, -0.5, 0));
	}
}
