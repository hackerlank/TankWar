#include "stdafx.h"
#include "MyGameCommand.h"
#include "../Common/Common.h"  //ʹ��get_ip����;

IMPLEMENT_SINGLETON(MyGameCommand)

	MyGameCommand::MyGameCommand(void)
	:
	isServerOwner(true)
{
	mSelfTankName = get_ip();
}


MyGameCommand::~MyGameCommand(void)
{
}


void MyGameCommand::SetMyInfomation(std::string playername ,std::string tankname ,int tankindex)
{
	//mSelfTankName = tankname;
	mTankIndex = tankindex;
	
}