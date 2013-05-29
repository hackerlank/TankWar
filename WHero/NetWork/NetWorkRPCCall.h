#ifndef NETWORKRPCCALL
#define NETWORKRPCCALL

//#pragma  once
#include "stdafx.h"
#include "CommonNetWorkProtocal.h"


void RPC_PlayerStateSync(RPCParameters *rpcParameters);

void RPC_PlayerStateSyncResponse(RPCParameters *rpcParameters);



void RPC_PlayerControlSync(RPCParameters *rpcParameters);

void RPC_PlayerControlSyncResponse(RPCParameters *rpcParameters);



void RPC_PlayerFireSync(RPCParameters* rpcParameters);

void RPC_PlayerFireSyncResponse(RPCParameters* rpcParameters);


void RPC_PlayerBulletCollisionSync(RPCParameters * rpcParameters);

void RPC_PlayerBulletCollisionSyncResponse(RPCParameters* rpcParameters);



#endif