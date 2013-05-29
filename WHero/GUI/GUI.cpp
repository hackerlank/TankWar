/*
 * GUI.cpp
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#include "GUI.h"

GUI::GUI(const Ogre::String &name,Ogre::RenderWindow *window,OIS::Mouse *mouse)
{
	m_pTrayMgr = new OgreBites::SdkTrayManager("OFTrayMgr", window, mouse, 0);
}

GUI::~GUI()
{
	delete m_pTrayMgr;
}

void GUI::MainMenuStateGuiInit()
{
	m_pTrayMgr->destroyAllWidgets();
	m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	m_pTrayMgr->showCursor();
	m_pTrayMgr->createButton(OgreBites::TL_CENTER, "EnterBtn", "Enter GameState", 250);
	m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit OgreFramework", 250);
	m_pTrayMgr->createLabel(OgreBites::TL_TOP, "MenuLbl","Menu mode", 250);
}

void GUI::MainMenuStateGuiUpdate(Ogre::FrameEvent  frameEvent)
{
	m_pTrayMgr->frameRenderingQueued(frameEvent);
}