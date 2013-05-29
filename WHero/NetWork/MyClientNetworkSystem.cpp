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

#include "stdafx.h"
#include "MyClientNetworkSystem.h"
#include "MyServerNetworkSystem.h"
#include "NetWorkRPCCall.h"
//#include "MyGame.h"
#include "MyGameCommand.h"

IMPLEMENT_SINGLETON(MyClientNetworkSystem)

	MyClientNetworkSystem::MyClientNetworkSystem(void)
{

	this->mClientPort = 0;
	this->mServerPort = 60001;
	mClient=RakNetworkFactory::GetRakPeerInterface();
	SocketDescriptor socketDescriptor(mClientPort,0);
	bool b;
	b = mClient->Startup(1, 30, &socketDescriptor, 1);
	//这里有待改进可以用更友好的方式 让用户重新配置客户端口
	if(!b)
	{
		assert(false && "Client Network Create Failed! May be Port Occupied!");
		throw "Can't init the NetworkSystem,Check the port whether be occupied";
	}
	mServerList.clear();    //清空Map 存储的系统地址

	REGISTER_STATIC_RPC(mClient, RPC_PlayerStateSyncResponse);	
	REGISTER_STATIC_RPC(mClient,RPC_PlayerControlSyncResponse);
	REGISTER_STATIC_RPC(mClient,RPC_PlayerFireSyncResponse);
	REGISTER_STATIC_RPC(mClient,RPC_PlayerBulletCollisionSyncResponse);

}

MyClientNetworkSystem::~MyClientNetworkSystem(void)
{
	if(this->mClient)
		RakNetworkFactory::DestroyRakPeerInterface(mClient);
}

void MyClientNetworkSystem::BroadastTheProbePacket(void)
{
	//255.255.255.255 mean broadcast

	mClient->Ping("255.255.255.255", mServerPort, true);//检测本机与局域网的指定端口的主机是否连通
	DWORD erro = GetLastError();
	if (erro = 10065)
	{
		//套接字操作尝试一个无法连接的主机。
		//这种情况应该是没有连接网线,所以只做单机测试
		mClient->Ping("127.0.0.1",mServerPort,true);
	}

	mServerList.clear();

}

void MyClientNetworkSystem::update(float dTime)
{
	// Holds packets
	Packet* p;	
	p = mClient->Receive();
	if (p==0)
		return;
	unsigned char packetIdentifier = GetPacketIdentifier(p);


	switch (packetIdentifier)
	{
	case ID_DISCONNECTION_NOTIFICATION:
		printf("连接正常终止\n");
		break;
	case ID_NEW_INCOMING_CONNECTION:
		printf("新客户 来自 %s 它的GUID是 %s\n", p->systemAddress.ToString(), p->guid.ToString());
		break;
	case ID_MODIFIED_PACKET:
		printf("警告！数据包被修改了！\n");
		break;
	case ID_CONNECTION_LOST:
		printf("连接断开\n");
		break;
	case ID_PONG:
		{
		// std::string  Ip;
		//Ip = p->systemAddress.ToString(false);
		//CommonNetWorkProtocal::IP = Ip;
 		}
		break;
	case ID_CONNECTION_REQUEST_ACCEPTED:
		// This tells the client they have connected
		::CoutDebugInfo("connection success!\n");
		break;

	default:
		break;
	}

	// We're done with the packet
	mClient->DeallocatePacket(p);


}

unsigned char MyClientNetworkSystem::GetPacketIdentifier(Packet *p)
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

void MyClientNetworkSystem::ConnectToTheServer(std::string ip)
{
	bool b = mClient->Connect(ip.c_str(), mServerPort,0, 0);

	this->mServerAddress = ::SystemAddress(ip.c_str(),mServerPort);

	if (b)
		CoutDebugInfo("Attempting connection\n");
	else
	{
		CoutDebugInfo("Bad connection attempt.  Terminating.\n");
		assert(false && "Bad connection attempt.  Terminating.\n");
	}

}

bool MyClientNetworkSystem::CloseConnection()
{
	mClient->CloseConnection(mServerAddress,true);

	mServerAddress = UNASSIGNED_SYSTEM_ADDRESS;

	return true;
}

bool MyClientNetworkSystem::SendPlayerStateSyncData(CommonNetWorkProtocal::TankInfo pss)
{
	CommonNetWorkProtocal::TankInfo t_pss;

//	memset(&t_pss,0,sizeof(t_pss));

	t_pss = pss;
 	return mClient->RPC("RPC_PlayerStateSync",(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, mServerAddress, false, 0, UNASSIGNED_NETWORK_ID,0);

}

bool MyClientNetworkSystem::SendPlayerControlSyncData(CommonNetWorkProtocal::MouseInfo mouseInfo){

	CommonNetWorkProtocal::MouseInfo t_mouseInfo;

	t_mouseInfo=mouseInfo;
	return mClient->RPC("RPC_PlayerControlSync",(char*)&t_mouseInfo,sizeof(t_mouseInfo)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, mServerAddress, false, 0, UNASSIGNED_NETWORK_ID,0);

}

bool MyClientNetworkSystem::SendPlayerFireSyncData(CommonNetWorkProtocal::FireInfo fireInfo){
	CommonNetWorkProtocal::FireInfo t_pss;

	t_pss = fireInfo;
	return mClient->RPC("RPC_PlayerFireSync",(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, mServerAddress, false, 0, UNASSIGNED_NETWORK_ID,0);

}

bool MyClientNetworkSystem::SendPlayerBulletCollisionSyncData(CommonNetWorkProtocal::BulletCollisionInfo collisionInfo){

	CommonNetWorkProtocal::BulletCollisionInfo t_pss;

	t_pss = collisionInfo;
	return mClient->RPC("RPC_PlayerBulletCollisionSync",(char*)&t_pss,sizeof(t_pss)*8, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, mServerAddress, false, 0, UNASSIGNED_NETWORK_ID,0);

}