#ifndef ABOUTGUISTATE_H_
#define ABOUTGUISTATE_H_

#include "../State/BaseState.h"
#include "../Common/SingletonT.h"
#include "../GameApp.h"

class AboutGUIState:public BaseState ,public SingletonT<AboutGUIState>
{
	SINGLETON_DEFINE(AboutGUIState)
public:
	AboutGUIState();
	~AboutGUIState();

	virtual void pause(void){}
	virtual void resume(void){}
	virtual void enter(void);
	virtual void exit(void);

	virtual void update(float timeSinceLastFrame);
	void	Init();

protected:
	void CameraInit();
	//���¼�������Ӧ����
	void createGUIEvent();
	virtual bool Back(const CEGUI::EventArgs& evt);

private:
	Ogre::SceneManager		*m_pSceneMgr;
	Ogre::RenderWindow		*m_pRenderWindow;


	Ogre::Camera			*m_pCamera;
	Ogre::Viewport			*m_pViewport;

	bool					m_pInit;
};
#endif