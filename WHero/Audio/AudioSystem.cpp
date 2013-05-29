#include "AudioSystem.h"

//#include "GamePlayerScript.h"

IMPLEMENT_SINGLETON(AudioSystem)



const std::string musicPath = "Media/audio/";
AudioSystem::AudioSystem(void)

	: device(audiere::OpenDevice())
{
	// ��������������ļ�;
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
	// ���ò���ģʽ
	streams[type]->setRepeat(isLoop);
	// ��������
// 	if (GamePlayerScript::GetSingleton().mUnsealMusic)
// 	{
// 		streams[type]->setVolume(GamePlayerScript::GetSingleton().mMusicVolume);
// 	}
// 	else
//	{
		streams[type]->setVolume(volum);
//	}
	// ����
	streams[type]->play();
}

void AudioSystem::stop(MusicType type)
{
	if (streams[type]->isPlaying())
	{
		streams[type]->stop();
	}
}