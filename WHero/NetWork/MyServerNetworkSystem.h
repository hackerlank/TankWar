
//#pragma once

#ifndef MYSEVERNETWORK
#define MYSEVERNETWORK

#include "stdafx.h"
#include "GameService.h"
#include "CommonNetWorkProtocal.h"

class MyServerNetworkSystem :public IGameService
{

	DECLARE_SINGLETON(MyServerNetworkSystem)

public:
	MyServerNetworkSystem(void);

	~MyServerNetworkSystem(void);

	bool DealPlayerStateSync( std::string guid,CommonNetWorkProtocal::TankInfo pss );
	bool DealPlayerStateSyncbroadcast( CommonNetWorkProtocal::TankInfo pss );
	bool DealPlayerControlSyncbroadcast(CommonNetWorkProtocal::MouseInfo mouseInfo);
	bool DealPlayerFireSyncbroadcast(CommonNetWorkProtocal::FireInfo fireInfo);
	bool DealPlayerBulletCollisionSyncbroadcast(CommonNetWorkProtocal::BulletCollisionInfo collisionInfo);
    virtual void update(float dTime);

private:

	unsigned char GetPacketIdentifier(Packet *p);
	//virtual void update(float dTime);
	SystemAddress ParseGuidToSystemAddress(std::string guid);

private:

	RakPeerInterface *m_Server;

	Packet* m_Packet;	

};


#endif
