#pragma once
//#include "ToolKit.h"
#include "../NetWork/stdafx.h"
#include "audiere.h"

enum MusicType
{
	CLICK_BUTTON,
	MENU_BACKGROUND,
	PLAYING_BACKGROUND,
	FIRE,
	ALERT
};

class AudioSystem
{
	DECLARE_SINGLETON(AudioSystem)
private:
	AudioSystem(void);
public:
	~AudioSystem(void);
	void play(MusicType type, int volum ,bool isLoop);
	void stop(MusicType type);
private:
	audiere::AudioDevicePtr device;
	std::vector<audiere::OutputStreamPtr> streams;
};

