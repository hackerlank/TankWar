#ifndef OPTIONGUISTATE_H_
#define OPTIONGUISTATE_H_

#include "../State/BaseState.h"
#include "../Common/SingletonT.h"
#include "../GameApp.h"


class OptionGUIState:public BaseState ,public SingletonT<OptionGUIState>
{
	SINGLETON_DEFINE(OptionGUIState)
public:
	OptionGUIState();
	~OptionGUIState();

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
	virtual bool Back(const CEGUI::EventArgs& evt);
/*	virtual bool Edit(const CEGUI::EventArgs& evt);*/
	virtual bool IsFullScreen(const CEGUI::EventArgs& evt);
	virtual bool Voice(const CEGUI::EventArgs& evt);


private:
	Ogre::SceneManager		*m_pSceneMgr;
	Ogre::RenderWindow		*m_pRenderWindow;


	Ogre::Camera			*m_pCamera;
	Ogre::Viewport			*m_pViewport;

	bool					m_pInit;


};
#endif