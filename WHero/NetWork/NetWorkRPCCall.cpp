
#pragma once
#include "stdafx.h"
#include "NetWorkRPCCall.h"
#include "MyServerNetworkSystem.h"
#include "MyGameCommand.h"
#include <iostream>
#include "../State/PlayingState.h"

using namespace std;


void RPC_PlayerStateSync(RPCParameters *rpcParameters)
{

		CommonNetWorkProtocal::TankInfo pss;

		memcpy_s(&pss,sizeof(pss),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

		bool ret;

		//cout<<"PSS: "<<pss.syncdata.x_position<<"  "<<pss.syncdata.y_position<<" "<<pss.syncdata.z_position<<endl;

		//ret = MyServerNetworkSystem::GetSingleton().DealPlayerStateSync(rpcParameters->sender.ToString(true),pss);

		ret = MyServerNetworkSystem::GetSingleton().DealPlayerStateSyncbroadcast(pss);
		assert(ret && "MyServerNetworkSystem::GetSingleton().DealPlayerStateSync : send Error!");

}

void RPC_PlayerStateSyncResponse(RPCParameters *rpcParameters)
{

	CommonNetWorkProtocal::TankInfo pss;

	memcpy_s(&pss,sizeof(pss),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

	//在该状态中处理tank包;
	PlayingState::getSingletonPtr()->DealTankSync(pss);
}


void RPC_PlayerControlSync(RPCParameters *rpcParameters){
	CommonNetWorkProtocal::MouseInfo mouseInfo;

	memcpy_s(&mouseInfo,sizeof(mouseInfo),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

	bool ret;


	ret = MyServerNetworkSystem::GetSingleton().DealPlayerControlSyncbroadcast(mouseInfo);
	assert(ret && "MyServerNetworkSystem::GetSingleton().DealPlayerControlSync : send Error!");


}

void RPC_PlayerControlSyncResponse(RPCParameters *rpcParameters){
	CommonNetWorkProtocal::MouseInfo pss;

	memcpy_s(&pss,sizeof(pss),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

	//在该状态中处理tank包;
	PlayingState::getSingletonPtr()->DealTankControlSync(pss);
}

void RPC_PlayerFireSync(RPCParameters* rpcParameters){
	CommonNetWorkProtocal::FireInfo pss;

	memcpy_s(&pss,sizeof(pss),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

	bool ret;

	ret = MyServerNetworkSystem::GetSingleton().DealPlayerFireSyncbroadcast(pss);
	assert(ret && "MyServerNetworkSystem::GetSingleton().DealPlayerFireSync : send Error!");
}

void RPC_PlayerFireSyncResponse(RPCParameters* rpcParameters){
	CommonNetWorkProtocal::FireInfo pss;

	memcpy_s(&pss,sizeof(pss),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

	PlayingState::getSingletonPtr()->DealTankFireSync(pss);
}

void RPC_PlayerBulletCollisionSync(RPCParameters * rpcParameters){
	CommonNetWorkProtocal::BulletCollisionInfo pss;

	memcpy_s(&pss,sizeof(pss),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

	bool ret;

	ret = MyServerNetworkSystem::GetSingleton().DealPlayerBulletCollisionSyncbroadcast(pss);
	assert(ret && "MyServerNetworkSystem::GetSingleton().DealPlayerBulletCollisionSync : send Error!");
}

void RPC_PlayerBulletCollisionSyncResponse(RPCParameters* rpcParameters){
	CommonNetWorkProtocal::BulletCollisionInfo pss;

	memcpy_s(&pss,sizeof(pss),rpcParameters->input,rpcParameters->numberOfBitsOfData/8);

	PlayingState::getSingletonPtr()->DealTankBulletCollisionSync(pss);
}