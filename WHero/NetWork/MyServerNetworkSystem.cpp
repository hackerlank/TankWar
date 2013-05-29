#include "stdafx.h"
#include "MyServerNetworkSystem.h"
#include "NetWorkRPCCall.h"

IMPLEMENT_SINGLETON(MyServerNetworkSystem)


MyServerNetworkSystem::MyServerNetworkSystem(void)
{

	m_Server=RakNetworkFactory::GetRakPeerInterface();

	CoutDebugInfo("server:Start the Server!\n");

	SocketDescriptor socketDescriptor(60001,0);

	bool b = m_Server->Startup(4, 30, &socketDescriptor, 1);

	m_Server->SetMaximumIncomingConnections(4);

	if (b)
		CoutDebugInfo("server:Server started, waiting for connections.\n");

	else
	{ 
		CoutDebugInfo("server:Server failed to start.  Warning!.\n");
		assert(false && "Server failed to start.  Warning.\n");
	}

	m_Server->SetOfflinePingResponse("SuperRacing",11);

	
	REGISTER_STATIC_RPC(m_Server,RPC_PlayerStateSync);
	REGISTER_STATIC_RPC(m_Server,RPC_PlayerControlSync);
	REGISTER_STATIC_RPC(m_Server,RPC_PlayerBulletCollisionSync);
	REGISTER_STATIC_RPC(m_Server,RPC_PlayerFireSync);


}


MyServerNetworkSystem::~MyServerNetworkSystem(void)
{
	
	m_Server->Shutdown(300);

	RakNetworkFactory::DestroyRakPeerInterface(m_Server);
	
	CoutDebugInfo("server:  server  initiative close! \n");
}


void MyServerNetworkSystem::update(float dTime)
{

	unsigned char packetIdentifier;

	m_Packet = m_Server->Receive();

	if (m_Packet==0)
	{
		return;
	}
	packetIdentifier = GetPacketIdentifier(m_Packet);

	switch (packetIdentifier)
	{

	case ID_DISCONNECTION_NOTIFICATION:

		CoutDebugInfo("server:connection end!\n");
		break;

	case ID_MODIFIED_PACKET:
		CoutDebugInfo("server:warning£¡the data packed modified£¡\n");
		break;

	case ID_CONNECTION_LOST:
		CoutDebugInfo("server:connection break!\n");
		break;

	case ID_PING_OPEN_CONNECTIONS:
		CoutDebugInfo("server:some one ping server!\n");
		break;
	case ID_NEW_INCOMING_CONNECTION:
		{
			CoutDebugInfo("server:new player %s\n",m_Packet->systemAddress.ToString(false));	

			//m_Server->RPC("RPC_EnterWaitingRoom",0, 0, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_Packet->systemAddress, false, 0, UNASSIGNED_NETWORK_ID,0);
			break;
		}

	default:

		break;
	}

	m_Server->DeallocatePacket(m_Packet);
}


unsigned char MyServerNetworkSystem::GetPacketIdentifier(Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{

		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	}
	else
		return (unsigned char) p->data[0];
}


SystemAddress MyServerNetworkSystem::ParseGuidToSystemAddress(std::string guid)
{
	//127.0.0.1:1132
	size_t colonPos = guid.find_first_of(':');

	std::string  ip = guid.substr(0,colonPos);
	std::string  port = guid.substr(colonPos+1,guid.size());

	std::stringstream str(port.c_str());
	unsigned short us_port = 0;
	str >> us_port;

	return SystemAddress(ip.c_str(),us_port);
}


bool MyServerNetworkSystem::DealPlayerStateSync( std::string guid,CommonNetWorkProtocal::TankInfo pss )
{
	CommonNetWorkProtocal::TankInfo t_pss;
	t_pss = pss;
	return m_Server->RPC("RPC_PlayerStateSyncResponse",
		(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED,
		0, ParseGuidToSystemAddress(guid), true, 0, UNASSIGNED_NETWORK_ID,0);
}


bool MyServerNetworkSystem::DealPlayerStateSyncbroadcast(CommonNetWorkProtocal::TankInfo pss)
{
	CommonNetWorkProtocal::TankInfo t_pss;
	t_pss = pss;
	return m_Server->RPC("RPC_PlayerStateSyncResponse",
		(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED,
		0, UNASSIGNED_SYSTEM_ADDRESS ,true, 0, UNASSIGNED_NETWORK_ID,0);
}

bool MyServerNetworkSystem::DealPlayerControlSyncbroadcast(CommonNetWorkProtocal::MouseInfo mouseInfo){
	CommonNetWorkProtocal::MouseInfo t_pss;
	t_pss = mouseInfo;
	return m_Server->RPC("RPC_PlayerControlSyncResponse",
		(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED,
		0, UNASSIGNED_SYSTEM_ADDRESS ,true, 0, UNASSIGNED_NETWORK_ID,0);
}

bool MyServerNetworkSystem::DealPlayerFireSyncbroadcast(CommonNetWorkProtocal::FireInfo fireInfo){
	CommonNetWorkProtocal::FireInfo t_pss;
	t_pss = fireInfo;
	return m_Server->RPC("RPC_PlayerFireSyncResponse",
		(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED,
		0, UNASSIGNED_SYSTEM_ADDRESS ,true, 0, UNASSIGNED_NETWORK_ID,0);
}

bool MyServerNetworkSystem::DealPlayerBulletCollisionSyncbroadcast(CommonNetWorkProtocal::BulletCollisionInfo collisionInfo){
	CommonNetWorkProtocal::BulletCollisionInfo t_pss;
	t_pss = collisionInfo;
	return m_Server->RPC("RPC_PlayerBulletCollisionSyncResponse",
		(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED,
		0, UNASSIGNED_SYSTEM_ADDRESS ,true, 0, UNASSIGNED_NETWORK_ID,0);
}