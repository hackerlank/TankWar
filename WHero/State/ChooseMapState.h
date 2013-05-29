#ifndef CHOOSEMAPSTATE_H_
#define CHOOSEMAPSTATE_H_

#include "../State/BaseState.h"
#include "../Common/SingletonT.h"
#include "../GameApp.h"


class ChooseMapState:public BaseState ,public SingletonT<ChooseMapState>
{
	SINGLETON_DEFINE(ChooseMapState)
public:
	~ChooseMapState();
	void	Init();
	virtual void pause(void){}
	virtual void resume(void){}
	virtual void enter(void);
	virtual void exit(void);
	virtual void update(float timeSinceLastFrame);


protected:
	void CameraInit();
	//绑定事件，与响应函数
	void createGUIEvent();
	void SetMap(int mapindex);
    bool handleLeft(const CEGUI::EventArgs& e);
	bool handleRight(const CEGUI::EventArgs& e);
	bool handleBack(const CEGUI::EventArgs& e);
	bool handleNext(const CEGUI::EventArgs& e);


private:
	ChooseMapState();
	Ogre::SceneManager		*m_pSceneMgr;
	Ogre::RenderWindow		*m_pRenderWindow;


	Ogre::Camera			*m_pCamera;
	Ogre::Viewport			*m_pViewport;

	bool					m_pInit;
	int mMapIndex;  //图编号
};
#endif