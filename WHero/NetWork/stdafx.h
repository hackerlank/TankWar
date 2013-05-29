// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "conio.h"
#include "windows.h"
#include <stdio.h>
#include <tchar.h>

//stl
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>

#include "MessageIdentifiers.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"
#include "GetTime.h"
#include "BitStream.h"


#include <iostream>

using namespace std;

//单件模式声明
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_SINGLETON(T)\
public:\
	static T##* GetSingletonPtr(void);\
	static T##& GetSingleton(void);\
	static void DestructSingleton(void);\
private:\
class DestructHelper\
{\
public:\
	~DestructHelper()\
	{\
	T##::DestructSingleton();\
	}\
};\
	static DestructHelper mDestructHelper;\
	static T##* m##T;\

//单件模式实现
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_SINGLETON(T)\
	T##* T##::m##T;\
	T##::DestructHelper T##::mDestructHelper;\
	T##* T##::GetSingletonPtr( void )\
{\
	if( !m##T  )\
	{\
	m##T  = new T##();\
	}\
	return m##T;\
}\
	T##& T##::GetSingleton( void )\
{\
	if( !m##T  )\
	{\
	m##T  = new T##();\
	}\
	return *m##T;\
}\
	void T##::DestructSingleton(void)\
{\
	if(m##T)\
  {\
  delete m##T;\
  m##T=0;\
  }\
}\
	\


#define CoutDebugInfo _cprintf

// TODO: reference additional headers your program requires here




