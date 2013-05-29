#ifndef MULTIPLAYERGUISTATE_H_
#define MULTIPLAYERGUISTATE_H_

#include "../State/BaseState.h"
#include "../Common/SingletonT.h"
#include "../GameApp.h"


class MultiplayerGUIState:public BaseState ,public SingletonT<MultiplayerGUIState>
{
	SINGLETON_DEFINE(MultiplayerGUIState)
public:
	MultiplayerGUIState();
	~MultiplayerGUIState();

	virtual void pause(void){}
	virtual void resume(void){}
	virtual void enter(void);
	virtual void exit(void);

	virtual void update(float timeSinceLastFrame);
	void	Init();

protected:
	void CameraInit();
	//绑定事件，与响应函数
	void createGUIEvent();
	virtual bool Create(const CEGUI::EventArgs& evt);
	virtual bool Join(const CEGUI::EventArgs& evt);
	virtual bool Back(const CEGUI::EventArgs& evt);
	virtual bool Search(const CEGUI::EventArgs& evt);
	virtual bool SelectChange(const CEGUI::EventArgs& evt);

private:
	void initServerInfoList(void);

private:
	Ogre::SceneManager		*m_pSceneMgr;
	Ogre::RenderWindow		*m_pRenderWindow;


	Ogre::Camera			*m_pCamera;
	Ogre::Viewport			*m_pViewport;

	bool					m_pInit;

	
};
#endif