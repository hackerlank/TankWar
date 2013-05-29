#include "AudioSystem.h"

//#include "GamePlayerScript.h"

IMPLEMENT_SINGLETON(AudioSystem)



const std::string musicPath = "Media/audio/";
AudioSystem::AudioSystem(void)

	: device(audiere::OpenDevice())
{
	// 在这里添加音乐文件;
	audiere::OutputStreamPtr stream;

	int fileNum = 5;
	std::string fileName[] = 
	{
		"message.mp3",
		"Soldiers Arrive.wav" ,
		"Bogey Approach.wav", 
		"bomb.wav",
		"alert.mp3"
	};

	for (int i=0; i<fileNum; ++i)
	{
		stream = audiere::OpenSound(device, (musicPath+fileName[i]).c_str(), false);
		streams.push_back(stream);
	}

}

AudioSystem::~AudioSystem(void)
{
}

void AudioSystem::play(MusicType type, int volum ,bool isLoop)
{
	// 设置播放模式
	streams[type]->setRepeat(isLoop);
	// 设置音量
// 	if (GamePlayerScript::GetSingleton().mUnsealMusic)
// 	{
// 		streams[type]->setVolume(GamePlayerScript::GetSingleton().mMusicVolume);
// 	}
// 	else
//	{
		streams[type]->setVolume(volum);
//	}
	// 播放
	streams[type]->play();
}

void AudioSystem::stop(MusicType type)
{
	if (streams[type]->isPlaying())
	{
		streams[type]->stop();
	}
}