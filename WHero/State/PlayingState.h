/*
 * PlayingState.h
 *
 *  Created on: June 23, 2012
 *      Author: hongxiaoqiang
 */

#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <vector>
#include "../State/BaseState.h"
#include "../Common/SingletonT.h"
#include "../GameApp.h"
#include "../Objects/Tank/BaseTank.h"
#include "../NetWork/CommonNetWorkProtocal.h"

class PlayingState : public BaseState, public SingletonT<PlayingState>
{
	SINGLETON_DEFINE(PlayingState)

public:
	~PlayingState(void);

	virtual void enter();
	virtual void exit();

	virtual void pause();
	virtual void resume();

	virtual void update(float timeSinceLaseFrame);

	virtual bool keyPressed(const OIS::KeyEvent&evt);
	virtual bool keyReleased(const OIS::KeyEvent&evt);
	virtual bool mouseMoved(const OIS::MouseEvent&evt);
	virtual bool mousePressed(const OIS::MouseEvent&evt, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent&evt, OIS::MouseButtonID id);

	//���ݴ����tank���֣��ж��Ƿ���tankList�д��ڸ����ֵ�tank;
	bool	isTankInList(std::string&);

	//����tank���ֺ�λ����Ϣ����һ��tank����;
	BaseTank *createTank(std::string name);

	//������յ���tank�������뵽tank�б���;
	void DealTankSync(CommonNetWorkProtocal::TankInfo _tankInfo);

	void DealTankControlSync(CommonNetWorkProtocal::MouseInfo _mouseInfo);

	void DealTankFireSync(CommonNetWorkProtocal::FireInfo _fireInfo);

	void DealTankBulletCollisionSync(CommonNetWorkProtocal::BulletCollisionInfo _bulletCollisionInfo );

protected:
	PlayingState(void);

	void createScene();
	void createCamera();
	void createLight();
	void createUI();
	void createUIEvent();
	void createNetWork();

	void destroyUI();
	void destroyScene();

	//---------------���¼�--------------
	bool onOK(const CEGUI::EventArgs& evt);
	bool onCancel(const CEGUI::EventArgs& evt);
	bool onReplayYES(const CEGUI::EventArgs& evt);
	bool onReplayNO(const CEGUI::EventArgs& evt);


	//��ײ���ģ�飬ʵ�ֶ����������еĸ�����֮�����ײ���;
	void checkCollision();

private:
	Ogre::Root*				m_pRoot;
	Ogre::RenderWindow*		m_pRenderWnd;
	Ogre::Viewport*			m_pViewport;
	Ogre::Log*				m_pLog;
	Ogre::Timer*			m_pTimer;

	Ogre::Camera*			m_pCamera;
	Ogre::SceneManager*		m_pSceneMgr;

	Ogre::Entity*			m_pMapEntity;
	Ogre::SceneNode*		m_pMapNode;

	//tank;
	BaseTank			*tank_m60;

	bool				m_isShowExit;  //�Ƿ���ʾ�˳�����;
	
	int					m_killNum;		//ɱ����;

	//�����Ϣ��������ά��һ�����״̬�б������������;
	//MyPlayerInfoMgr		*m_pPlayerMgr;
	map<std::string, BaseTank*>	m_TankList;
};
#endif
