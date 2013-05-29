/*
 * BaseTank.h
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#ifndef BASETANK_H_
#define BASETANK_H_

#include <Ogre.h>
#include "../GameApp.h"

class BaseTank
{
public:
	BaseTank();
	virtual ~BaseTank();
	
protected:
	Ogre::SceneManager		*m_pSceneMgr;

	Ogre::Entity			*m_pBodyEntity;
	Ogre::SceneNode			*m_pBodyNode;
};
#endif