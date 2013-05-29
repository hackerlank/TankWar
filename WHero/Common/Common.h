#ifndef COMMON_H
#define COMMON_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include   <winsock.h> 
#include   <wsipx.h> 
#include   <wsnwlink.h> 
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib") //�������ӵ�ws2_32.lib�����


class IFrameListener
{
public:
	/**
	  ״̬����, ÿһ֡����
	  @timeSinceLastFrame	����һ֡��ʱ��(����s)
	*/
	virtual void update( float timeSinceLastFrame ) = 0;

	/**
		��Ⱦ�����״̬, ÿһ֡����
		@timeSinceLastFrame	����һ֡��ʱ��(����s)
	*/
	virtual void updateAfterRender( float timeSinceLastFrame) {}
};
#endif

//---------------------------------------------------��ȡ����IP-----------------------------------------

char   *   get_ip() 
{ 

	WORD   wVersionRequested   =   MAKEWORD(1,   1); 
	WSADATA   wsaData; 

	if   (WSAStartup(wVersionRequested,   &wsaData))   
		return   0; 


	char   hostname[256]; 
	int   res   =   gethostname(hostname,   sizeof(hostname)); 
	if   (res   !=   0) 
		return   0; 

	hostent*   pHostent   =   gethostbyname(hostname); 
	if   (pHostent==NULL) 
		return   0; 

	hostent&   he   =   *pHostent; 

	sockaddr_in   sa; 

	memcpy   (   &sa.sin_addr.s_addr,   he.h_addr_list[0],he.h_length); 
	WSACleanup(); 

	return   inet_ntoa(sa.sin_addr); 
}

//----------------------------------------------------��һ��----------------------
