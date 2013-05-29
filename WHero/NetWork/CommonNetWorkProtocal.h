#pragma once
#include "stdafx.h"
#include <Ogre.h>

enum TankMotionID;
namespace CommonNetWorkProtocal
{
	const static unsigned long MaxStrLen = 20;
	const static unsigned long MaxPlayerNum = 4;


 	struct  SyncData
 	{
 		Ogre::Real  x_position;
 		Ogre::Real  y_position;
		Ogre::Real  z_position;	
	
		bool		m_bIsTurnLeft;	  
		bool		m_bIsTurnRight;	  
		
     	
 	};


	struct TankInfo
	{
		//bool  isFire;

		//char  hited_tankName[MaxStrLen];

		char tankName[MaxStrLen];

		SyncData	syncdata;


	};

struct  MouseInfo
   {
        Ogre::Real deltaYaw;
	    Ogre::Real deltaPitch;

        char tankName[MaxStrLen];
   };

struct  FireInfo
   {
	 //int hitSpace;
	 char tankName[MaxStrLen];
   };

struct  BulletCollisionInfo
 {
	//bool isHit;
	char tankName[MaxStrLen];
  };

}


