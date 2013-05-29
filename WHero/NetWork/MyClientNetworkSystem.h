/*
-----------------------------------------------------------------------------
This source file is part of SuperRacing (A Car Racing Game)

Copyright (c) 2009-2010 Kenshin

Usage of this program is free for non-commercial use and licensed under the
the terms of the MIT License.

for more info please visit 

http://superacing.sourceforge.net/forum
-----------------------------------------------------------------------------
*/
#ifndef MYCLIENTNETWORK
#define  MYCLIENTNETWORK
#include "stdafx.h"
#include "GameService.h"
#include "CommonNetWorkProtocal.h"


class MyClientNetworkSystem :public IGameService
{

	DECLARE_SINGLETON(MyClientNetworkSystem)

public:

	MyClientNetworkSystem(void);

	~MyClientNetworkSystem(void);

	void BroadastTheProbePacket(void);  

	void ConnectToTheServer(std::string ip); 

	bool CloseConnection();           

	bool SendPlayerStateSyncData(CommonNetWorkProtocal::TankInfo pss);

	bool SendPlayerControlSyncData(CommonNetWorkProtocal::MouseInfo mouseInfo);

	bool SendPlayerFireSyncData(CommonNetWorkProtocal::FireInfo  fireInfo);

	bool SendPlayerBulletCollisionSyncData(CommonNetWorkProtocal::BulletCollisionInfo collisionInfo);

	virtual void update(float dTime);  

private:

	unsigned char GetPacketIdentifier(Packet *p);                               
//	virtual void update(float dTime);                                         

private:
	RakPeerInterface *mClient;                                                  
	int mClientPort;                                                           
	int mServerPort;                                                           
	SystemAddress  mServerAddress;                                             
	std::map<std::string,SystemAddress> mServerList;                           

};


#endif;
