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

	//根据传入的tank名字，判断是否在tankList中存在该名字的tank;
	bool	isTankInList(std::string&);

	//根据tank名字和位置信息创建一个tank对象;
	BaseTank *createTank(std::string name);

	//处理接收到的tank包，加入到tank列表中;
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

	//---------------绑定事件--------------
	bool onOK(const CEGUI::EventArgs& evt);
	bool onCancel(const CEGUI::EventArgs& evt);
	bool onReplayYES(const CEGUI::EventArgs& evt);
	bool onReplayNO(const CEGUI::EventArgs& evt);


	//碰撞检测模块，实现对整个场景中的各对象之间的碰撞检测;
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

	bool				m_isShowExit;  //是否显示退出界面;
	
	int					m_killNum;		//杀敌数;

	//玩家信息管理器，维护一张玩家状态列表，管理所有玩家;
	//MyPlayerInfoMgr		*m_pPlayerMgr;
	map<std::string, BaseTank*>	m_TankList;
};
#endif
