/*
 * GUI.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#ifndef GUI_H_
#define GUI_H_

#include "../Tankwar.h"

class GUI
{
public:
	GUI(const Ogre::String &name,Ogre::RenderWindow *window,OIS::Mouse *mouse);
	~GUI();

	void MainMenuStateGuiInit();
	void MainMenuStateGuiUpdate(Ogre::FrameEvent  frameEvent);      //render

private:
		OgreBites::SdkTrayManager*	m_pTrayMgr;
};
#endif