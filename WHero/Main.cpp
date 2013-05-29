/*
 * Main.cpp
 *
 *  Created on: June 20, 2012
 *      Author: xujie
 */

#include "GameApp.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char** argv)
#endif
{
	GameApp mywar;
	try
	{
		mywar.StartGame();
	}
	catch (std::exception& e)
	{
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.what(), "An exception has occurred", MB_OK
			| MB_ICONERROR |MB_TASKMODAL);
#else
		fprintf(stderr, "An excption has occurred: %s\n", e.what());
#endif
	}

	return 0;
}